import pygame
from pygame.locals import *
from pygame.time import Clock
from OpenGL.GL import *
from OpenGL.GLUT import *

import random


from constants import *
from utils import *


current_frame = 0
frame_rate = 8
frame_counter = 0


class Game:
    def __init__(self) -> None:
        self.spider_x = SCREEN_WIDTH // 2
        self.spider_y = 0
        self.spider_fuel = SPIDER_MAX_FUEL
        self.spider_textures = []
        self.spider_injured_texture = None
        self.blood_texture = None
        

        self.gun_x = GUN_WIDTH // 2 + 10
        self.gun_y = -SCREEN_HEIGHT // 2 + 10
        self.gun_texture = None
        # self.gun_movement = GunMovement.STOP
        self.gun_movement = "s"
        

        self.bullets = []
        self.bullet_texture = None

        self.load_textures()

    def load_textures(self):
        img_spider0 = load_image(image_paths["spider-0"])
        img_spider1 = load_image(image_paths["spider-1"])
        self.spider_textures.append(img_spider0)
        self.spider_textures.append(img_spider1)

        self.spider_injured_texture = load_image(image_paths["spider-injured"])
        self.blood_texture = load_image(image_paths["blood"])

        self.gun_texture = load_image(image_paths["rocket"])
        self.bullet_texture = load_image(image_paths["bullet"])

    def draw_text(self, texture_id: int, x: int, y: int, width: int, height: int):
        glEnable(GL_TEXTURE_2D)
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

    def draw_gun(self):
        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, self.gun_texture)

        glBegin(GL_QUADS)

        glTexCoord2f(0, 0)
        glVertex2f(self.gun_x, self.gun_y)
        glTexCoord2f(1, 0)
        glVertex2f(self.gun_x + GUN_WIDTH, self.gun_y)
        glTexCoord2f(1, 1)
        glVertex2f(self.gun_x + GUN_WIDTH, self.gun_y + GUN_HEIGHT)
        glTexCoord2f(0, 1)
        glVertex2f(self.gun_x, self.gun_y + GUN_HEIGHT)

        glEnd()
        glDisable(GL_TEXTURE_2D)

    def move_gun(self):
        pass
        if self.gun_movement =='r':
            self.gun_x += GUN_MOVE_X_VELOCITY
        elif self.gun_movement == 'l':
            self.gun_x -= GUN_MOVE_X_VELOCITY
        elif self.gun_movement == 'u':
            self.gun_y += GUN_MOVE_Y_VELOCITY
            
        elif self.gun_movement == 'd':
            self.gun_y -= GUN_MOVE_Y_VELOCITY

        if self.gun_x < SCREEN_BOUNDS[0]:
            self.gun_x = SCREEN_BOUNDS[0]

        elif self.gun_x + GUN_WIDTH > SCREEN_BOUNDS[1]:
            self.gun_x = SCREEN_BOUNDS[1] - GUN_WIDTH

        elif self.gun_y > GUN_MAX_UP_POSITION:
            self.gun_y = GUN_MAX_UP_POSITION

        elif self.gun_y < GUN_MAX_DOWN_POSITION:
            self.gun_y = GUN_MAX_DOWN_POSITION

    def draw_spider(self):
        """spider texture is animated. the spider will move in entire screen.
        if spider collides with screen edge then its back and forth movement will be reversed.
        """
        global current_frame, frame_counter
        spider_texture = self.spider_textures[current_frame]
        frame_counter += 1
        if frame_counter >= frame_rate:
            current_frame += 1
            frame_counter = 0
        if current_frame >= len(self.spider_textures):
            current_frame = 0

        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, spider_texture)

        glBegin(GL_QUADS)

        glTexCoord2f(0, 0)
        glVertex2f(self.spider_x, self.spider_y)
        glTexCoord2f(1, 0)
        glVertex2f(self.spider_x + SPIDER_WIDTH, self.spider_y)
        glTexCoord2f(1, 1)
        glVertex2f(self.spider_x + SPIDER_WIDTH, self.spider_y + SPIDER_HEIGHT)
        glTexCoord2f(0, 1)
        glVertex2f(self.spider_x, self.spider_y + SPIDER_HEIGHT)

        glEnd()
        glDisable(GL_TEXTURE_2D)

    def move_spider(self):
        """Update spider position and handle boundary collisions"""
        self.spider_x += SPIDER_VELOCITY[0]
        self.spider_y += SPIDER_VELOCITY[1]

        if (
            self.spider_x < SCREEN_BOUNDS[0]
            or self.spider_x + SPIDER_WIDTH > SCREEN_BOUNDS[1]
        ):
            SPIDER_VELOCITY[0] *= -1
        if (
            self.spider_y < SCREEN_BOUNDS[2]
            or self.spider_y + SPIDER_HEIGHT > SCREEN_BOUNDS[3]
        ):
            SPIDER_VELOCITY[1] *= -1

    def shoot_bullet(self):
        """
        when up key press then this will add bullet into list of bullets.
        bullet will start from gun position and move upwards.
        if bullet goes out of screen then it will be removed from list.
        """
        bullet_x = self.gun_x + GUN_WIDTH // 2 - BULLET_WIDTH // 2
        bullet_y = self.gun_y + GUN_HEIGHT
        self.bullets.append([bullet_x, bullet_y])

    def move_bullets(self):
        for bullet in self.bullets:
            bullet[1] += BULLET_VELOCITY
        self.bullets = [bullet for bullet in self.bullets if bullet[1] < SCREEN_HEIGHT]

    def draw_bullets(self):
        for bullet in self.bullets:
            # self.draw_text(self.bullet_texture, bullet[0], bullet[1], BULLET_WIDTH, BULLET_HEIGHT)
            x, y = bullet

            glEnable(GL_TEXTURE_2D)
            glBindTexture(GL_TEXTURE_2D, self.bullet_texture)
            glBegin(GL_QUADS)

            glTexCoord2f(0, 0)
            glVertex2f(x, y)
            glTexCoord2f(1, 0)
            glVertex2f(x + BULLET_WIDTH, y)
            glTexCoord2f(1, 1)
            glVertex2f(x + BULLET_WIDTH, y + BULLET_HEIGHT)
            glTexCoord2f(0, 1)
            glVertex2f(x, y + BULLET_HEIGHT)

            glEnd()
            glDisable(GL_TEXTURE_2D)
            
    def check_collision(self):
        for bullet in self.bullets:
            bullet_x, bullet_y = bullet
            if (
                bullet_x < self.spider_x + SPIDER_WIDTH
                and bullet_x + BULLET_WIDTH > self.spider_x
                and bullet_y < self.spider_y + SPIDER_HEIGHT
                and bullet_y + BULLET_HEIGHT > self.spider_y
            ):
                # self.spider_injured()
                self.bullets.remove(bullet)
                self.spider_fuel -= 1
                if self.spider_fuel == 0:
                    text = render_text("Game Over", 50, (255, 0, 0))
                    self.draw_text(text,0,0,100,100)

    def render(self):
        self.draw_spider()
        self.move_spider()

        self.draw_bullets()
        self.move_bullets()
        

        self.draw_gun()
        self.move_gun()
        
        self.check_collision()