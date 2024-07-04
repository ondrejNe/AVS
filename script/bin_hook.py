# https://docs.platformio.org/en/latest/scripting/construction_environments.html#scripting-envs

"""
Firstly .elf file is created.
Then .hex file is created from .elf file.
After that .bin file is created from .elf file.
Subsequently, all the files are copied to the bin directory.
"""

Import("env")
import glob
import shutil
import os

# Build also the .hex file
env.AddPostAction(
    "$BUILD_DIR/${PROGNAME}.elf",
    env.VerboseAction(
        " ".join(
            [
                "$OBJCOPY", "-O", "ihex", "-R", ".eeprom", "$BUILD_DIR/${PROGNAME}.elf", "$BUILD_DIR/${PROGNAME}.hex"
            ]
        ),
        "Built $BUILD_DIR/${PROGNAME}.hex"
    )
)

# The target directory relative to the PlatformIO project root
target_dir = "bin"
# Ensures the target directory exists
os.makedirs(target_dir, exist_ok=True)

def copy_progname_files(source, target, env):
    # This line gets the base environment directory, which typically includes the .pio folder
    base_dir = env.subst("$PROJECT_BUILD_DIR")
    progname = env.get("PROGNAME")

    # Adjust the search_pattern to ensure it looks in the right location for all file types
    search_patterns = [
        os.path.join(base_dir, env.get("PIOENV"), f"{progname}.elf"),
        os.path.join(base_dir, env.get("PIOENV"), f"{progname}.hex"),
        os.path.join(base_dir, env.get("PIOENV"), f"{progname}.bin")
    ]

    files_to_copy = []
    for pattern in search_patterns:
        # Adding files from each pattern to the list
        files_to_copy.extend(glob.glob(pattern))

    # Copy each file
    for file_path in files_to_copy:
        shutil.copy(file_path, target_dir)

    print(f"Copied {len(files_to_copy)} files to {target_dir}/")

# Instead of attaching to the .elf file creation, attach this to the end of the build process
env.AddPostAction("$BUILD_DIR/${PROGNAME}.bin", env.VerboseAction(copy_progname_files, "Copying ${PROGNAME} related files to bin directory"))
