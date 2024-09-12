import pygame
from pygame.locals import *
from pygame.time import Clock
from OpenGL.GL import *
from OpenGL.GLUT import *

import random


from constant import *
from utils import *


current_frame = 0
frame_rate = 5
frame_counter = 0


class Game:
    def __init__(self):
        self.mario_x = SCREEN_WIDTH // 4
        self.mario_y = GROUND_STARTING_HEIGHT_MARIO

        self.jump_velocity = JUMP_VELOCITY
        self.gravity = -0.3
        self.background_x = 0

        self.is_moving_right = False
        self.is_moving_left = False
        self.is_jumping = False
        self.is_game_over = False

        self.pipes = []
        self.pipe_speed = BACKGROUND_SPEED

        self.mario_sprite = []
        self.load_textures()

        self.theme_sound = pygame.mixer.Sound(sounds_paths["theme"])
        self.theme_sound.set_volume(1.1)

        self.jump_sound = pygame.mixer.Sound(sounds_paths["jump"])
        self.jump_sound.set_volume(0.8)

        self.game_over_sound = pygame.mixer.Sound(sounds_paths["game_over"])

        self.theme_sound.play()

        
    def load_textures(self):
        self.mario_idle = load_image(image_paths["mario_idle"])
        self.mario_jump = load_image(image_paths["mario_jump"])
        self.mario_run1 = load_image(image_paths["mario_run1"])
        self.mario_run2 = load_image(image_paths["mario_run2"])
        self.mario_run3 = load_image(image_paths["mario_run3"])

        self.bg_image = load_image(image_paths["bg_image"])
        self.bg_image_pipe = load_image(image_paths["bg_image_pipe"])

        self.mario_sprite.append(self.mario_run1)
        self.mario_sprite.append(self.mario_run2)
        self.mario_sprite.append(self.mario_run3)
        
    def draw_text(self,texture_id:int, x: int, y: int, width: int, height: int):
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
        
    def draw_mario(self):
        global current_frame, frame_counter
        if self.is_jumping:
            mario_texture = self.mario_jump
        if self.is_moving_right:  # sprint animation
            mario_texture = self.mario_sprite[current_frame]
            frame_counter += 1
            if frame_counter >= frame_rate:
                current_frame += 1
                frame_counter = 0
            if current_frame >= len(self.mario_sprite):
                current_frame = 0
        else:
            mario_texture = self.mario_idle

        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, mario_texture)

        glBegin(GL_QUADS)

        glTexCoord2f(0, 0)
        glVertex2f(self.mario_x, self.mario_y)
        glTexCoord2f(1, 0)
        glVertex2f(self.mario_x + MARIO_WIDTH, self.mario_y)
        glTexCoord2f(1, 1)
        glVertex2f(self.mario_x + MARIO_WIDTH, self.mario_y + MARIO_HEIGHT)
        glTexCoord2f(0, 1)
        glVertex2f(self.mario_x, self.mario_y + MARIO_HEIGHT)

        glEnd()
        glDisable(GL_TEXTURE_2D)

    def draw_background(self):
        # Draw background and handle its movement
        glEnable(GL_TEXTURE_2D)
        glBindTexture(GL_TEXTURE_2D, self.bg_image)
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

        # Draw the repeating part
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

        self.background_x -= self.pipe_speed
        if self.background_x <= -SCREEN_WIDTH:
            self.background_x = 0

    def move_forward(self):
        if self.is_moving_right:
            self.pipe_speed = FAST_BACKGROUND_SPEED
        else:
            self.pipe_speed = BACKGROUND_SPEED

    def generate_pipe(self):
        if len(self.pipes) == 0 or self.pipes[-1][0] < SCREEN_WIDTH - 200:
            pipe_y = GROUND_STARTING_HEIGHT_PIPE
            # random x position for pipe
            pipe_x = random.randint(SCREEN_WIDTH, SCREEN_WIDTH + 250)
            self.pipes.append([pipe_x, pipe_y])

    def draw_pipes(self):
        for pipe in self.pipes:
            # Draw each pipe
            pipe_x, pipe_y = pipe
            glEnable(GL_TEXTURE_2D)
            glBindTexture(GL_TEXTURE_2D, self.bg_image_pipe)
            glBegin(GL_QUADS)
            glTexCoord2f(0, 0)
            glVertex2f(pipe_x, pipe_y)
            glTexCoord2f(1, 0)
            glVertex2f(pipe_x + PIPE_WIDTH, pipe_y)
            glTexCoord2f(1, 1)
            glVertex2f(pipe_x + PIPE_WIDTH, pipe_y + PIPE_HEIGHT)
            glTexCoord2f(0, 1)
            glVertex2f(pipe_x, pipe_y + PIPE_HEIGHT)
            glEnd()
            glDisable(GL_TEXTURE_2D)

            # Move pipes
            pipe[0] -= self.pipe_speed

            # Remove pipes that go off the screen
            if pipe[0] + PIPE_WIDTH < 0:
                self.pipes.remove(pipe)

    def handle_collision(self):
        for pipe in self.pipes:
            pipe_x, pipe_y = pipe
            if (
                self.mario_x + (MARIO_WIDTH - 25) > pipe_x
                and self.mario_x < pipe_x + PIPE_WIDTH
            ):
                if self.mario_y < pipe_y + PIPE_HEIGHT:
                    self.is_game_over = True

    def jump(self):
        if self.is_jumping:
            self.jump_sound.play()
            self.mario_y += self.jump_velocity
            self.jump_velocity += self.gravity
            if self.mario_y <= GROUND_STARTING_HEIGHT_MARIO:
                self.mario_y = GROUND_STARTING_HEIGHT_MARIO
                self.is_jumping = False
                self.jump_velocity = JUMP_VELOCITY

    def draw_game_over(self):
        self.jump_sound.stop()
        self.theme_sound.stop()
        self.game_over_sound.play()

        texture_id, text_width, text_height = render_text("Game Over", 100, (255, 0, 0))

        self.draw_text(texture_id, SCREEN_WIDTH // 2 - text_width // 2, SCREEN_HEIGHT // 2, text_width, text_height)
   

    def update(self):
        if self.is_game_over:
            # pass
            self.draw_game_over()
        else:
            self.draw_background()
            self.draw_pipes()
            self.generate_pipe()
            self.handle_collision()
            self.draw_mario()
            self.jump()
