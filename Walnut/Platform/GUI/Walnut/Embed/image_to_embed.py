import os
from PIL import Image
import io

def process_image_to_embed_as_c_array(input_file_path, embed_file_path, resize_dims=None, output_format='PNG'):
    """
    Reads an image file, optionally scales it, converts it to PNG, 
    and writes it as a const uint8_t C array in an embed file.

    :param input_file_path: Path to the input image (e.g., .ico, .jpg, .png).
    :param embed_file_path: Path to the embed file where the C array will be written.
    :param output_format: Desired output format for the image (default is 'PNG').
    :param resize_dims: Tuple (width, height) to scale the image, or None for original dimensions.
    """
    try:
        # Extract the name for the C array
        array_name = f"g_{os.path.splitext(os.path.basename(input_file_path))[0]}"

        # Open and process the image
        with Image.open(input_file_path) as img:
            img = img.convert("RGBA")  # Ensure consistent format

            # Resize the image if resize_dims are provided
            if resize_dims:
                img = img.resize(resize_dims, Image.ANTIALIAS)  # High-quality scaling

            # Create a BytesIO buffer and save the image as PNG to it
            buffer = io.BytesIO()
            img.save(buffer, format=output_format)

            # Get the byte data from the buffer
            byte_data = buffer.getvalue()

        # Write to the embed file in C array format
        with open(embed_file_path, "w") as embed_file:
            # Write the header for the C array
            embed_file.write(f"const uint8_t {array_name}[] = {{\n")

            # Write the byte data as comma-separated hex values
            for i, byte in enumerate(byte_data):
                if i % 12 == 0:  # Format to have 12 bytes per line
                    embed_file.write("\n    ")
                embed_file.write(f"0x{byte:02X}, ")

            # Close the array
            embed_file.write("\n};\n")

        print(f"C array written to embed file: {embed_file_path}")

    except Exception as e:
        print(f"Error processing image to C array: {e}")
    
input_file = r"D:\3DM_Code\VoxelWorld\frontend\RenderEngine\Walnut\Platform\GUI\Walnut\Embed\3dmorphicIcon.ico"
output_file = r"D:\3DM_Code\VoxelWorld\frontend\RenderEngine\Walnut\Platform\GUI\Walnut\Embed\3DM-Icon.embed"
process_image_to_embed_as_c_array(input_file, output_file)
