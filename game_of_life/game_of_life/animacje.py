import os

frames_dir = "frames"

probabilities = ["0.05", "0.10", "0.30", "0.60", "0.75", "0.80", "0.95"]

for prob in probabilities:
    input_pattern = f"{frames_dir}/p({prob})/frame_%d.ppm"
    output_file = f"wyniki/p({prob}).mp4"
    command = f"ffmpeg -framerate 10 -i {input_pattern} -c:v libx264 -pix_fmt yuv420p {output_file}"
    os.system(command)
