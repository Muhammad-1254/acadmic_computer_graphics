from pygame.locals import *
import pygame

from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

from constants import *
from game import Game



def main():
    pygame.init()
    pygame.mixer.init()
    pygame.font.init()
    
    
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MAJOR_VERSION, 3)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_MINOR_VERSION, 1)
    pygame.display.gl_set_attribute(pygame.GL_CONTEXT_PROFILE_MASK, pygame.GL_CONTEXT_PROFILE_CORE)
    
    pygame.display.set_caption("Spider Shooter")
    pygame.display.set_mode((SCREEN_WIDTH, SCREEN_HEIGHT), DOUBLEBUF | OPENGL)
    
    # glClearColor(0.0, 0.0, 0.0, 1.0)
    # glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT)
    
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    
    glOrtho(SCREEN_BOUNDS[0],SCREEN_BOUNDS[1],SCREEN_BOUNDS[2],SCREEN_BOUNDS[3], -1, 1)
    
    game = Game()
    
    running = True
    while running:
        glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT)
        
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == KEYDOWN:
                
                # for moving the gun
                if event.key == K_RIGHT:
                    game.gun_movement = "r"
                if event.key == K_LEFT:
                    game.gun_movement = "l"
                if event.key == K_UP:
                    game.gun_movement = "u"
                if event.key == K_DOWN:
                    game.gun_movement = "d"
                
                
                # for shooting the bullet
                if event.key == K_SPACE:
                    game.shoot_bullet()
        
            elif event.type == KEYUP:
                if event.key == K_RIGHT or event.key == K_LEFT or event.key == K_UP or event.key == K_DOWN:
                    game.gun_movement = 's'
                
                
                # for closing game
                if event.key == K_q:
                    running = False
                # for restarting game
                if event.key == K_r:
                    game = Game()
        
        
        # clock.tick(120)
        game.render()
        pygame.display.flip()
        pygame.time.wait(20)

    pygame.quit()
    
 
 
if __name__ == "__main__":
    main()