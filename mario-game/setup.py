from cx_Freeze import setup, Executable

# Dependencies and build options
options = {
    'build_exe': {
        'packages': ['pygame', 'OpenGL'],
        'include_files': ['assets/']  # Add your asset directories here
    }
}

# Setup configuration
setup(
    name='MarioGame',
    version='1.0',
    description='My Pygame and PyOpenGL Project',
    options=options,
    executables=[Executable('main.py', base='Win32GUI')]  # Use 'Win32GUI' for a windowed app
)
