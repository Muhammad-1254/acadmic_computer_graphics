from pygame.locals import *
import pygame

from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

from constants import *
from game import Game
from utils import *


def main():
    get_window_size()
    pygame.init()
    pygame.mixer.init()
    pygame.font.init()
    clock = pygame.time.Clock() # for fps
    
    
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MAJOR_VERSION, 3)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MINOR_VERSION, 1)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_PROFILE_MASK, pygame.GL_CONTEXT_PROFILE_CORE)
    
    pygame.display.set_caption("Ghost Shooter")
    pygame.display.set_mode((WINDOW_WIDTH, WINDOW_HEIGHT), DOUBLEBUF | OPENGL)
    
    glClearColor(0.0, 0.0, 0.0, 1.0)
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    
    glOrtho(0,SCREEN_WIDTH,0,SCREEN_HEIGHT, -1, 1)
    
    game = Game()
    
    running = True
    while running:
        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT)
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            if event.type == KEYDOWN:
                # for closing game
                if event.key == K_q:
                    running = False
                # for restarting game
                if event.key == K_r:
                    game.restart()
            

        game.render()
        pygame.display.flip()
        pygame.time.wait(80)
        

    pygame.quit()
    
 
 
if __name__ == "__main__":
    main()