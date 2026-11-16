import time
import struct
import serial
import numpy as np
import bettercam

# --- INSTELLINGEN ---
COM_PORT = "COM5"      #poort van de PICO
BAUD_RATE = 921600
NUM_LEDS = 24           # 3 x 8 doorverbonden LED's op Bus 0
TARGET_FPS = 60
BRIGHTNESS = 0.5       # Veilig voor directe USB-voeding (max ~720 mA)

def build_packet(bus_id: int, rgb_array: np.ndarray) -> bytes:
    """Bouwt het OSCAP binaire pakketje: [0xAA, 0x55, BUS_ID, LEN_H, LEN_L, DATA...]"""
    raw_bytes = rgb_array.astype(np.uint8).tobytes()
    header = struct.pack(">BBBH", 0xAA, 0x55, bus_id, len(raw_bytes))
    return header + raw_bytes

def main():
    print(f"Verbinden met OSCAP controller op {COM_PORT}...")
    ser = serial.Serial(COM_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Wacht even tot de Pico klaar is na serial connectie

    print("Starten van DXGI Screen Capture...")
    camera = bettercam.create(output_color="RGB")
    camera.start(target_fps=TARGET_FPS)

    print("OSCAP PoC draait! Druk op Ctrl+C om te stoppen.")
    try:
        while True:
            frame = camera.get_latest_frame()
            if frame is None:
                continue

            # Pak de bovenste 10% van het scherm voor deze eerste test[cite: 1]
            height, width, _ = frame.shape
            top_region = frame[0:int(height * 0.10), :, :]

            # Verdeel de bovenrand in 24 blokken en bereken de gemiddelde RGB-kleur[cite: 1]
            splits = np.array_split(top_region, NUM_LEDS, axis=1)
            led_colors = np.array([block.mean(axis=(0, 1)) for block in splits])

            # Pas veilige helderheid toe[cite: 1]
            led_colors = led_colors * BRIGHTNESS

            # Bouw pakket voor Bus 0 en verstuur[cite: 1]
            packet = build_packet(bus_id=0, rgb_array=led_colors)
            ser.write(packet)

    except KeyboardInterrupt:
        print("\nAfsluiten... LEDs uitzetten.")
        off_packet = build_packet(bus_id=0, rgb_array=np.zeros((NUM_LEDS, 3)))
        ser.write(off_packet)
    finally:
        camera.stop()
        ser.close()

if __name__ == "__main__":
    main()