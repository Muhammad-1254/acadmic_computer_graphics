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
        self.bg_image = None
        self.background_y = 0
        self.spider_fuel = SPIDER_MAX_FUEL
        self.total_bullets = TOTAL_BULLETS
        self.is_game_over = False
        self.is_spider_died = False
        self.blood_shed = []
        
        self.spider_x = SCREEN_WIDTH // 2
        self.spider_y = 0
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
        self.load_sounds()
        
        

    def load_textures(self):

        img_spider0 = load_image(image_paths["spider-0"])
        img_spider1 = load_image(image_paths["spider-1"])
        self.spider_textures.append(img_spider0)
        self.spider_textures.append(img_spider1)

        self.bg_image = load_image(image_paths["bg"])
        
        self.spider_injured_texture = load_image(image_paths["spider-injured"])
        self.blood_texture = load_image(image_paths["blood"])

        self.gun_texture = load_image(image_paths["rocket"])
        self.bullet_texture = load_image(image_paths["bullet"])

    def load_sounds(self):
        self.shoot_sound = pygame.mixer.Sound(sound_paths['shoot'])
        self.shoot_sound.set_volume(1.5)
        
        self.theme_sound = pygame.mixer.Sound(sound_paths['theme'])
        self.theme_sound.set_volume(0.25)
        
        self.game_won = pygame.mixer.Sound(sound_paths['game_won'])
        self.game_won.set_volume(1.0)
        
        self.game_over = pygame.mixer.Sound(sound_paths['game_over'])
        self.game_over.set_volume(1.0)
        
        self.theme_sound.play(-1)
        
    def draw_background(self):
       # Draw background and handle its movement
        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, self.bg_image)
        glBegin(GL_QUADS)
        
        
        glTexCoord2f(0, 0); glVertex2f(BACKGROUND_X_0,  self.background_y+BACKGROUND_Y_0)
        glTexCoord2f(1, 0); glVertex2f(BACKGROUND_X_1,  self.background_y+BACKGROUND_Y_0)
        glTexCoord2f(1, 1); glVertex2f(BACKGROUND_X_1,   self.background_y+BACKGROUND_Y_1)
        glTexCoord2f(0, 1); glVertex2f(BACKGROUND_X_0,   self.background_y+BACKGROUND_Y_1)
        
        glEnd()

        # # Draw the repeating part
        glBegin(GL_QUADS)
        
        glTexCoord2f(0, 0); glVertex2f(BACKGROUND_X_0,  self.background_y+BACKGROUND_Y_1)
        glTexCoord2f(1, 0); glVertex2f(BACKGROUND_X_1,  self.background_y+BACKGROUND_Y_1)
        glTexCoord2f(1, 1); glVertex2f(BACKGROUND_X_1,   self.background_y+BACKGROUND_Y_1*3)
        glTexCoord2f(0, 1); glVertex2f(BACKGROUND_X_0,   self.background_y+BACKGROUND_Y_1*3)
        
        glEnd()

        glDisable(GL_TEXTURE_2D)
        self.background_y -= BACKGROUND_SPEED
        if self.background_y <= -SCREEN_HEIGHT:
            self.background_y= 0
        
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
        self.shoot_sound.play()
        
        if self.total_bullets == 0: self.is_game_over = True
        elif self.total_bullets < self.spider_fuel: self.is_game_over = True
        else: self.total_bullets -= 1
        
        

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
                bullet_x < self.spider_x + SPIDER_WIDTH-30
                and bullet_x + BULLET_WIDTH > self.spider_x
                and bullet_y < self.spider_y + SPIDER_HEIGHT-15
                and bullet_y + BULLET_HEIGHT > self.spider_y
            ):
                self.blood_shed.append([self.spider_x, self.spider_y])
                self.bullets.remove(bullet)
                self.spider_fuel -= 1
                if self. spider_fuel== 0:
                    self.is_spider_died = True
                    break
    def draw_blood_shed(self, ):
        for blood in self.blood_shed:
            x, y = blood
            glEnable(GL_TEXTURE_2D)
            glBindTexture(GL_TEXTURE_2D, self.blood_texture)
            glBegin(GL_QUADS)

            glTexCoord2f(0, 0)
            glVertex2f(x+SPIDER_WIDTH/2, y+SPIDER_HEIGHT//2)
            glTexCoord2f(1, 0)
            glVertex2f(x + BLOOD_SHED_WIDTH, y)
            glTexCoord2f(1, 1)
            glVertex2f(x + BLOOD_SHED_WIDTH, y + BLOOD_SHED_WIDTH)
            glTexCoord2f(0, 1)
            glVertex2f(x, y + BLOOD_SHED_WIDTH)

            glEnd()
            glDisable(GL_TEXTURE_2D)
            
    def draw_fuel(self):
        texture_id, texture_w,texture_h = render_text(f"Fuel: {self.spider_fuel}", 50, (0, 255, 0))
        self.draw_text(texture_id,-SCREEN_WIDTH//2+10,SCREEN_HEIGHT//2-60, texture_w,texture_h )
    def draw_bullets_count(self):
        texture_id, texture_w,texture_h = render_text(f"Bullets: {self.total_bullets}", 50, (0, 255, 0))
        self.draw_text(texture_id,-SCREEN_WIDTH//2+10,SCREEN_HEIGHT//2-110, texture_w,texture_h )
    def draw_time(self):
        from datetime import datetime, timedelta
        max_time = timedelta(minutes=1)
        # print(max_time)
        
        
    def restart_game(self):
        self.shoot_sound.stop()
        self.game_over.stop()
        self.game_won.stop()
        self.theme_sound.play(-1)
        
        self.spider_x = SCREEN_WIDTH // 2
        self.spider_y = 0
        self.spider_fuel = SPIDER_MAX_FUEL
        self.gun_x = GUN_WIDTH // 2 + 10
        self.gun_y = -SCREEN_HEIGHT // 2 + 10
        self.gun_movement = "s"
        self.bullets = []
        self.is_game_over = False
        self.total_bullets = TOTAL_BULLETS
        self.is_spider_died = False
        self.blood_shed = []
        
        

    def draw_game_end(self):
        self.theme_sound.stop()
        self.shoot_sound.stop()
        
        if self.is_spider_died:
            self.game_won.play(-1)
            texture_id, texture_w,texture_h = render_text("Spider Died", 100, (255, 0, 0))
            screen_w,screen_h = get_screen_size_by_percentage(0.25)
            self.draw_text(texture_id,SCREEN_WIDTH//2-texture_w+10,screen_h, texture_w,texture_h )
        elif self.is_game_over:
            self.game_over.play(-1)
            texture_id, texture_w,texture_h = render_text("Game Over", 100, (0, 0, 255))
            screen_w,screen_h = get_screen_size_by_percentage(0.25)
            self.draw_text(texture_id,SCREEN_WIDTH//2-texture_w+10,screen_h, texture_w,texture_h )
        
        texture_id, texture_w,texture_h = render_text("Press r to restart or q to quit", 32, (255, 255, 255))
        screen_w,screen_h = get_screen_size_by_percentage(0.25)
        self.draw_text(texture_id,SCREEN_WIDTH//2-texture_w-40,screen_h-50, texture_w,texture_h )
            
        
    def render(self):
        self.draw_background()
        self.draw_fuel()
        self.draw_bullets_count()
        self.draw_blood_shed()
        
        if self.is_spider_died or self.is_game_over:
            self.draw_game_end()
        else:
            self.draw_spider()
            self.move_spider()

            self.draw_bullets()
            self.move_bullets()
            
            self.draw_gun()
            self.move_gun()
            
            self.check_collision()