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

        # self.load_sounds()

        self.ghost_top_radius = GHOST_WIDTH // 2
        self.ghost_relative_x = GHOST_WIDTH
        self.ghost_relative_y = GHOST_HEIGHT
        
        self.ghost_relative_x =100
        self.ghost_relative_y =(13*self.ghost_relative_x)/9
        self.ghost_top_radius = self.ghost_relative_x // 2
    
    def draw_ghost(self):
        self.draw_ghost_cap()
        self.draw_ghost_center()
        self.draw_ghost_eyes()
        self.draw_ghost_bottom()

    def draw_ghost_cap(self):
        cx = self.ghost_relative_x * 1.5
        cy = self.ghost_relative_y
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

        glVertex2f(self.ghost_relative_x, self.ghost_relative_y)
        glVertex2f(self.ghost_relative_x + GHOST_WIDTH, self.ghost_relative_y)
        glVertex2f(
            self.ghost_relative_x + GHOST_WIDTH,
            self.ghost_relative_y - GHOST_HEIGHT // 3,
        )
        glVertex2f(
            self.ghost_relative_x, self.ghost_relative_y - GHOST_HEIGHT // 3
        )
        glEnd()

    def draw_ghost_eyes(self):
        cx = self.ghost_relative_x * 1.3
        cy = self.ghost_relative_y
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

        cx = self.ghost_relative_x * 1.7
        cy = self.ghost_relative_y
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
        cx = self.ghost_relative_x * 1.25
        cy = self.ghost_relative_y - GHOST_HEIGHT // 3
        radius = self.ghost_top_radius // 2
        glColor(1, 1, 1)
        glVertex2f(cx, cy)  # Center of the circle
        for angle in range(180, 271):  # 180° to 270° for third quadrant
            theta = math.radians(angle)
            x = cx + radius * math.cos(theta)
            y = cy + radius * math.sin(theta)
            glVertex2f(x, y)
        glEnd()

        glBegin(GL_TRIANGLES)
        glColor(1, 1, 1)
        # right triangle left side
        glVertex2f(
            self.ghost_relative_x * 1.25,
            self.ghost_relative_y - (GHOST_HEIGHT // 3) * 1.55,
        )
        glVertex2f(
            self.ghost_relative_x * 1.25,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )
        glVertex2f(
            self.ghost_relative_x * 1.35,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )

        # center triangle
        glVertex2f(
            self.ghost_relative_x * 1.35,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )
        glVertex2f(
            self.ghost_relative_x * 1.4,
            self.ghost_relative_y - (GHOST_HEIGHT // 3) * 1.55,
        )
        glVertex2f(
            self.ghost_relative_x * 1.45,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )

        glVertex2f(
            self.ghost_relative_x * 1.45,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )
        glVertex2f(
            self.ghost_relative_x * 1.5,
            self.ghost_relative_y - (GHOST_HEIGHT // 3) * 1.55,
        )
        glVertex2f(
            self.ghost_relative_x * 1.55,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )

        glVertex2f(
            self.ghost_relative_x * 1.55,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )
        glVertex2f(
            self.ghost_relative_x * 1.6,
            self.ghost_relative_y - (GHOST_HEIGHT // 3) * 1.55,
        )
        glVertex2f(
            self.ghost_relative_x * 1.65,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )

        # left triangle right side
        glVertex2f(
            self.ghost_relative_x * 1.75,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )
        glVertex2f(
            self.ghost_relative_x * 1.75,
            self.ghost_relative_y - (GHOST_HEIGHT // 3) * 1.55,
        )
        glVertex2f(
            self.ghost_relative_x * 1.65,
            self.ghost_relative_y - (GHOST_HEIGHT // 3),
        )
        glEnd()

        glBegin(GL_POLYGON)
        glColor(1, 1, 1)
        cx = self.ghost_relative_x * 1.75
        cy = self.ghost_relative_y - GHOST_HEIGHT // 3
        radius = self.ghost_top_radius // 2
        glVertex2f(cx, cy)  # Center of the circle
        for angle in range(360, 269, -1):  # 180° to 270° for third quadrant
            theta = math.radians(angle)
            x = cx + radius * math.cos(theta)
            y = cy + radius * math.sin(theta)
            glVertex2f(x, y)
        glEnd()

    def move_ghost(self):
        random_x = random.uniform(GHOST_WIDTH//2, GHOST_WIDTH)
        random_y = (13*random_x)/9
        self.ghost_relative_x = random_x
        self.ghost_relative_y = random_y        
        self.ghost_top_radius = random_x // 2




    def load_sounds(self):
        self.shoot_sound = pygame.mixer.Sound(sound_paths["shoot"])
        self.shoot_sound.set_volume(1.5)

        self.theme_sound = pygame.mixer.Sound(sound_paths["theme"])
        self.theme_sound.set_volume(0.25)

        self.game_won = pygame.mixer.Sound(sound_paths["game_won"])
        self.game_won.set_volume(1.0)

        self.game_over = pygame.mixer.Sound(sound_paths["game_over"])
        self.game_over.set_volume(1.0)

        self.theme_sound.play(-1)


    def restart(self):
        pass
    def render(self):
        self.draw_ghost()
        # self.move_ghost()