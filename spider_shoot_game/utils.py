
import pygame
from pygame.locals import *
from OpenGL.GL import *
from OpenGL.GLUT import *
from  constants import *
import os

def load_image(image_path: str) -> int:
    try:
        # Load the image using pygame
        image = pygame.image.load(image_path)
    except pygame.error as e:
        print(f"Unable to load image at {image_path}: {e}")
        return 0
    
    # Convert the image to a format with an alpha channel (RGBA)
    image = image.convert_alpha()  # Ensure the image has an alpha channel

    # Convert image to string data with RGBA format
    texture_data = pygame.image.tostring(image, "RGBA", True)
    width, height = image.get_size()

    # Generate a new texture ID
    texture_id = glGenTextures(1)

    # Bind the texture
    glBindTexture(GL_TEXTURE_2D, texture_id)

    # Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)  

    # Enable blending for transparency
    glEnable(GL_BLEND)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)  # Set blend function for transparency

    # Upload the texture data to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data)

    # Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0)

    return texture_id

def render_text(text:str, font_size:int, color:tuple)->int:
    font = pygame.font.SysFont("Arial", font_size)
    text_surface = font.render(text, True, color)
    text_data = pygame.image.tostring(text_surface, "RGBA", True)
    w,h = text_surface.get_size()
    
    texture_id = glGenTextures(1)
    glBindTexture(GL_TEXTURE_2D, texture_id)
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR)
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, text_data)
    glBindTexture(GL_TEXTURE_2D, 0)
    return texture_id,w,h

def get_screen_size_by_percentage(percentage:float)->tuple:
    return int((SCREEN_WIDTH//2)*percentage), int((SCREEN_HEIGHT//2)*percentage)

def get_window_size_by_percentage(percentage:float)->tuple:
    return int((WINDOW_WIDTH//2)*percentage), int((WINDOW_HEIGHT//2)*percentage)

def get_correct_path(path):
    return os.path.join(os.getcwd(),path)
    
def get_window_size():
    import ctypes
    global WINDOW_WIDTH, WINDOW_HEIGHT
    user32 = ctypes.windll.user32
    (w,h) = user32.GetSystemMetrics(0), user32.GetSystemMetrics(1)
    WINDOW_WIDTH = w
    WINDOW_HEIGHT = h