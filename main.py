import oliver, devraj

print("Hello, world!")

oliver.serial_listen() 

"""
import os
from pydub import AudioSegment

# Directory containing the .m4a files
directory = '/site/'

# Iterate over all files in the directory
for filename in os.listdir(directory):
    if filename.endswith('.m4a'):
        # Construct full file path
        m4a_path = os.path.join(directory, filename)
        # Define the new file name with .mp3 extension
        mp3_path = os.path.join(directory, os.path.splitext(filename)[0] + '.mp3')
        
        # Load the .m4a file
        audio = AudioSegment.from_file(m4a_path, format='m4a')
        # Export as .mp3
        audio.export(mp3_path, format='mp3')
        
        print(f"Converted {m4a_path} to {mp3_path}")
"""