import pygame
from pygame.locals import *
from pygame.time import Clock
from OpenGL.GL import *
from OpenGL.GLUT import *

from math import *

from constant import *
from utils import *


class Game:
    def __init__(self):
        self.car_x = SCREEN_WIDTH // 4
        self.car_y = GROUND_STARTING_HEIGHT_CAR

        self.background_x = 0
        self.wheel_rotation_angle = 0

        self.is_moving_right = False
        self.is_moving_left = False

        self.background_speed = BACKGROUND_SPEED

        self.load_textures()

        self.theme_sound = pygame.mixer.Sound(sounds_paths["theme"])
        self.theme_sound.set_volume(1.1)
        self.theme_sound.play()

    def load_textures(self):
        self.bg_image = load_image(image_paths["bg_image"])

    def draw_text(self, texture_id: int, x: int, y: int, width: int, height: int):
        glEnable(GL_TEXTURE_2D)
        glColor3f(1, 1, 1)
        glBindTexture(GL_TEXTURE_2D, texture_id)

        glBegin(GL_QUADS)
        glTexCoord2f(0, 0)
        glVertex2f(x, y)

        glTexCoord2f(1, 0)
        glVertex2f(x + width, y)

        glTexCoord2f(1, 1)
        glVertex2f(x + width, y + height)

        glTexCoord2f(0, 1)
        glVertex2f(x, y + height)
        glEnd()

        glBindTexture(GL_TEXTURE_2D, 0)
        glDisable(GL_TEXTURE_2D)

    
    def draw_car(self):

        self.draw_rounded_rectangle(self.car_x, self.car_y, CAR_WIDTH, CAR_HEIGHT, )
        
            
        if self.is_moving_right:
            self.wheel_rotation_angle += self.background_speed
        elif self.is_moving_left:
            self.wheel_rotation_angle +=  self.background_speed
        
 
 
        # Draw car wheels
        s_wheel_x = self.car_x + CAR_WIDTH / 6
        glPushMatrix()
        glTranslatef(s_wheel_x, self.car_y, 0)
        glRotatef(self.wheel_rotation_angle, 0, 0, 1)
        self.draw_wheel(0, 0, CAR_WHEEL_RADIUS)
        glPopMatrix()

        glPushMatrix()
        glTranslatef(s_wheel_x, self.car_y, 0)
        self.draw_wheel_arch(0, 0, CAR_WHEEL_RADIUS)
        glPopMatrix()
        
        s_wheel_x  = self.car_x +  CAR_WIDTH - CAR_WIDTH / 6
        glPushMatrix()
        glTranslatef(s_wheel_x, self.car_y, 0)
        glRotatef(self.wheel_rotation_angle, 0, 0, 1)
        self.draw_wheel(0, 0, CAR_WHEEL_RADIUS)
        glPopMatrix()
        
        glPushMatrix()
        glTranslatef(s_wheel_x, self.car_y, 0)
        self.draw_wheel_arch(0, 0, CAR_WHEEL_RADIUS)
        glPopMatrix()
        


    def draw_rounded_rectangle(self, x, y, width, height, ):
        # draw left rectangle
        s_x = x
        s_y = y
        e_x = s_x + width/4
        e_y = s_y + height/1.9
        glBegin(GL_QUADS)
        glColor3f(0.0, 0.5, 1.0)  
        glVertex2f(s_x, s_y) 
        glVertex2f(e_x, y)
        glVertex2f(e_x, e_y)
        glVertex2f(s_x, e_y)
        glEnd()
        
        # Draw center rectangle (without corners)
        s_x = e_x
        s_y = y
        e_x = s_x + width/2
        e_y = s_y + height
        glBegin(GL_QUADS)
        glColor3f(0.0, 0.5, 1.0)  
        glVertex2f(s_x, s_y)  
        glVertex2f(e_x, y)
        glVertex2f(e_x, e_y)
        glVertex2f(s_x, e_y)
        glEnd()
        
        
        # draw right rectangle
        s_x = e_x
        s_y = y
        e_x = s_x + width/4
        e_y = s_y + height/1.9
        glBegin(GL_QUADS)
        glColor3f(0.0, 0.5, 1.0)  
        glVertex2f(s_x, s_y)  
        glVertex2f(e_x, y)
        glVertex2f(e_x, e_y)
        glVertex2f(s_x, e_y)
        glEnd()
        
        
      
        

        
        

  
    def draw_wheel_arch(self, x, y, radius):
        # Draw semi-circle for wheel arch (only upper half of the circle)
        glColor3f(0,1,1)  # Same as car body color to make a cutout
        glBegin(GL_TRIANGLE_FAN)
        glVertex2f(x, y)  # Center of wheel arch
        for angle in range(0, 181):
            rad = radians(angle)
            glVertex2f(x + cos(rad) * radius, y + sin(rad) * radius)
        glEnd()
        

        
    def draw_wheel(self, x, y, radius):
        glBegin(GL_TRIANGLE_FAN)
        glColor3f(0, 0, 0)
        glVertex2f(x, y)
        for i in range(361):
            angle = i * 3.14159 / 180
            glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius)
        glEnd()

        self.draw_wheel_nuts(x, y, radius)


    def draw_wheel_nuts(self, x, y, radius):
        glBegin(GL_QUADS)
        glColor3f(1, 1, 0)
        glVertex3f(x - 2, y + radius / 2.2, 1)
        glVertex3f(x + 2, y + radius / 2.2, 1)
        glVertex3f(x + 2, y + radius / 2.2 + 2, 1)
        glVertex3f(x - 2, y + radius / 2.2 + 2, 1)
        glEnd()

        glBegin(GL_QUADS)
        glVertex2f(x - 2, y - radius / 2.2)
        glVertex2f(x + 2, y - radius / 2.2)
        glVertex2f(x + 2, y - radius / 2.2 - 2)
        glVertex2f(x - 2, y - radius / 2.2 - 2)
        glEnd()

        glBegin(GL_QUADS)
        glVertex2f(x + radius / 2.2, y - 2)
        glVertex2f(x + radius / 2.2, y + 2)
        glVertex2f(x + radius / 2.2 + 2, y + 2)
        glVertex2f(x + radius / 2.2 + 2, y - 2)
        glEnd()

        glBegin(GL_QUADS)
        glVertex2f(x - radius / 2.2, y - 2)
        glVertex2f(x - radius / 2.2, y + 2)
        glVertex2f(x - radius / 2.2 - 2, y + 2)
        glVertex2f(x - radius / 2.2 - 2, y - 2)
        glEnd()
        
    def draw_background(self):
        # Draw background and handle its movement
        glEnable(GL_TEXTURE_2D)
        glColor3f(1, 1, 1)
        glBindTexture(GL_TEXTURE_2D, self.bg_image)
        
        # there are three image for repeating bg
        # left image 
         
        glBegin(GL_QUADS)
        glTexCoord2f(0, 0)
        glVertex2f(self.background_x - SCREEN_WIDTH, 0)
        glTexCoord2f(1, 0)
        glVertex2f(self.background_x , 0)
        glTexCoord2f(1, 1)
        glVertex2f(self.background_x , SCREEN_HEIGHT)
        glTexCoord2f(0, 1)
        glVertex2f(self.background_x - SCREEN_WIDTH, SCREEN_HEIGHT)
        glEnd()
        
        # middle image
        glBegin(GL_QUADS)
        glTexCoord2f(0, 0)
        glVertex2f(self.background_x, 0)
        glTexCoord2f(1, 0)
        glVertex2f(self.background_x + SCREEN_WIDTH, 0)
        glTexCoord2f(1, 1)
        glVertex2f(self.background_x + SCREEN_WIDTH, SCREEN_HEIGHT)
        glTexCoord2f(0, 1)
        glVertex2f(self.background_x, SCREEN_HEIGHT)
        glEnd()
        

        # right image
        glBegin(GL_QUADS)
        glTexCoord2f(0, 0)
        glVertex2f(self.background_x + SCREEN_WIDTH, 0)
        glTexCoord2f(1, 0)
        glVertex2f(self.background_x + 2 * SCREEN_WIDTH, 0)
        glTexCoord2f(1, 1)
        glVertex2f(self.background_x + 2 * SCREEN_WIDTH, SCREEN_HEIGHT)
        glTexCoord2f(0, 1)
        glVertex2f(self.background_x + SCREEN_WIDTH, SCREEN_HEIGHT)
        glEnd()

        glDisable(GL_TEXTURE_2D)

        # if self.is_moving_left:
        self.background_x = self.background_x+ self.background_speed
            
            
        if self.background_x <= -SCREEN_WIDTH:
            self.background_x = 0
        elif self.background_x >= SCREEN_WIDTH:
            self.background_x = 0

    def move_forward(self):
        pass

    def render(self):
        self.draw_background()
        self.draw_car()
