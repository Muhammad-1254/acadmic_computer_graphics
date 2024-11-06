import pygame
from pygame.locals import *
from pygame.time import Clock
from OpenGL.GL import *
from OpenGL.GLUT import *
import math

import random


from constants import *
from utils import *


current_frame = 0
frame_rate = 8
frame_counter = 0


class Game:
    def __init__(self) -> None:

        self.position_x = 500
        self.position_y = 500
        self.ghost_top_radius = GHOST_WIDTH // 2

        self.load_sounds()
    
    def draw_ghost(self):
        self.draw_ghost_cap()
        self.draw_ghost_center()
        self.draw_ghost_eyes()
        self.draw_ghost_bottom()


    def draw_ghost_cap(self):
        cx = self.position_x+GHOST_WIDTH//2
        cy = self.position_y
        radius = self.ghost_top_radius
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)
        glVertex2f(cx, cy)
        for angle in range(0, 181):
            theta = math.radians(angle)
            x = cx + radius * math.cos(theta)
            y = cy + radius * math.sin(theta)
            glVertex2f(x, y)
        glEnd()
        
    def draw_ghost_center(self):
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)

        glVertex2f(self.position_x, self.position_y)
        glVertex2f(self.position_x + GHOST_WIDTH, self.position_y)
        glVertex2f(
            self.position_x + GHOST_WIDTH,
            self.position_y - GHOST_HEIGHT // 2.5,
        )
        glVertex2f(
            self.position_x, self.position_y - GHOST_HEIGHT // 2.5
        )

        
        glEnd()
    def draw_ghost_eyes(self):
        cx = self.position_x+GHOST_WIDTH//3.1
        cy = self.position_y
        radius_x = self.ghost_top_radius // 4
        radius_y = self.ghost_top_radius // 3.5
        glBegin(GL_POLYGON)
        glColor(0, 0, 0)
        glVertex2f(cx, cy)
        for angle in range(0, 361):
            theta = math.radians(angle)
            x = cx + radius_x * math.cos(theta)
            y = cy + radius_y * math.sin(theta)
            glVertex2f(x, y)
        glEnd()
        
        cx = self.position_x+GHOST_WIDTH//1.4
        cy = self.position_y
        radius_x = self.ghost_top_radius // 4
        radius_y = self.ghost_top_radius // 3.5
        glBegin(GL_POLYGON)
        glColor(0, 0, 0)
        glVertex2f(cx, cy)
        for angle in range(0, 361):
            theta = math.radians(angle)
            x = cx + radius_x * math.cos(theta)
            y = cy + radius_y * math.sin(theta)
            glVertex2f(x, y)
        glEnd()
        
    def draw_ghost_bottom(self):
        # for left quarter curve
        glBegin(GL_POLYGON)
        cx = self.position_x  + GHOST_WIDTH//4.25 
        cy = self.position_y - GHOST_HEIGHT // 3
        radius = self.ghost_top_radius // 2
        glColor(1, 1, 1)
        glVertex2f(cx, cy)  # Center of the circle
        for angle in range(180, 271):  # 180° to 270° for third quadrant
            theta = math.radians(angle)
            x = cx + radius * math.cos(theta)
            y = cy + radius * math.sin(theta)
            glVertex2f(x, y)
        glEnd()

        # right triangle left side
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)
        left = GHOST_WIDTH/4
        right = GHOST_WIDTH/2.7
        center = (left+right)/2
        glVertex2f(
            self.position_x + left,
            self.position_y - (GHOST_HEIGHT / 3) ,
        )
        glVertex2f(
            self.position_x + center,
            self.position_y - (GHOST_HEIGHT / 3)*1.75,
        )
        glVertex2f(
            self.position_x + right,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glEnd()
        
              
        # Center triangle
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)
        left = GHOST_WIDTH/2.8
        right = GHOST_WIDTH/2.3
        center = (left+right)/2
        glVertex2f(
            self.position_x + left,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glVertex2f(
            self.position_x + center,
            self.position_y - (GHOST_HEIGHT / 3)*1.75,
        )
        glVertex2f(
            self.position_x + right,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glEnd()
        
          # Center triangle
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)

        left = GHOST_WIDTH/2.3
        right = GHOST_WIDTH/1.9
        center = (left+right)/2
        glVertex2f(
            self.position_x + left,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glVertex2f(
            self.position_x + center,
            self.position_y - (GHOST_HEIGHT / 3)*1.75,
        )
        glVertex2f(
            self.position_x + right,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glEnd()
                # Center triangle
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)

        left = GHOST_WIDTH/1.9
        right = GHOST_WIDTH/1.6
        center = (left+right)/2
        glVertex2f(
            self.position_x + left,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glVertex2f(
            self.position_x + center,
            self.position_y - (GHOST_HEIGHT / 3)*1.75,
        )
        glVertex2f(
            self.position_x + right,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glEnd()
                # Center triangle
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)
        left = GHOST_WIDTH/1.6
        right = GHOST_WIDTH/1.35
        center = (left+right)/2
        glVertex2f(
            self.position_x + left,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glVertex2f(
            self.position_x + center,
            self.position_y - (GHOST_HEIGHT / 3)*1.75,
        )
        glVertex2f(
            self.position_x + right,
            self.position_y - (GHOST_HEIGHT / 3),
        )
        glEnd()
        

        


        # left curve
        glBegin(GL_POLYGON)
        glColor(1, 1, 1)
        cx = self.position_x + GHOST_WIDTH//1.31
        cy = self.position_y - GHOST_HEIGHT // 3
        radius = self.ghost_top_radius // 2
        glVertex2f(cx, cy)  # Center of the circle
        for angle in range(360, 269, -1):  # 180° to 270° for third quadrant
            theta = math.radians(angle)
            x = cx + radius * math.cos(theta)
            y = cy + radius * math.sin(theta)
            glVertex2f(x, y)
        glEnd()




    def move_ghost(self):
        global GHOST_WIDTH, GHOST_HEIGHT
        
        random_w = random.uniform(130,200)
        GHOST_WIDTH = random_w
        GHOST_HEIGHT = (13*GHOST_WIDTH)/9
        
        random_x = random.uniform(GHOST_WIDTH, SCREEN_WIDTH-GHOST_WIDTH)
        random_y = random.uniform(GHOST_HEIGHT, SCREEN_HEIGHT-GHOST_HEIGHT)
        
        self.position_x = random_x
        self.position_y = random_y       
        self.ghost_top_radius = GHOST_WIDTH // 2



    def load_sounds(self):
        self.shoot_sound = pygame.mixer.Sound(sound_paths['theme'])
        self.shoot_sound.set_volume(1.5)
        self.shoot_sound.play()

    def draw_background(self):
        self.bg_image = load_image(image_paths['bg'])
        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, self.bg_image)
        glBegin(GL_QUADS)
        
        glTexCoord2f(0, 0); glVertex2f(0, 0 )
        glTexCoord2f(1, 0); glVertex2f(SCREEN_WIDTH,  0  )
        glTexCoord2f(1, 1); glVertex2f(SCREEN_WIDTH,  SCREEN_HEIGHT )
        glTexCoord2f(0, 1); glVertex2f(0,  SCREEN_HEIGHT )
        
        glEnd()
        glDisable(GL_TEXTURE_2D)



    def restart(self):
        pass
    def render(self):
        self.draw_background()
        self.draw_ghost()
        self.move_ghost()