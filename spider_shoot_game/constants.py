WINDOW_WIDTH = 1080
WINDOW_HEIGHT= 720

SCREEN_WIDTH = 600
SCREEN_HEIGHT = 600

SPIDER_WIDTH = 80
SPIDER_HEIGHT = 130
SPIDER_VELOCITY = [8, 8]  
SCREEN_BOUNDS = [-SCREEN_WIDTH//2, SCREEN_WIDTH, -SCREEN_HEIGHT//2, SCREEN_HEIGHT//2]  # [left, right, bottom, top]

BACKGROUND_X_0 = SCREEN_BOUNDS[0]
BACKGROUND_X_1 = SCREEN_BOUNDS[1]
BACKGROUND_Y_0 = SCREEN_BOUNDS[2]
BACKGROUND_Y_1 = SCREEN_BOUNDS[3]
BACKGROUND_SPEED = 5

BLOOD_SHED_WIDTH = SPIDER_WIDTH//3

GUN_WIDTH = 100
GUN_HEIGHT = 150
GUN_MOVE_X_VELOCITY = 15
GUN_MOVE_Y_VELOCITY = 7
GUN_MAX_UP_POSITION =-(SCREEN_HEIGHT//2 -100)
GUN_MAX_DOWN_POSITION = -(SCREEN_HEIGHT//2 +50)




SPIDER_MAX_FUEL = 10 # 10 bullets
TOTAL_BULLETS =15



BULLET_WIDTH = 20
BULLET_HEIGHT = 40
BULLET_VELOCITY = 35


GROUND_STARTING_HEIGHT_GUN = 0
GROUND_STARTING_HEIGHT_SPIDER = 0




image_paths={
    "spider-injured": "assets/images/spider-injured.png",
    "spider-0": "assets/images/spider-0.png",
    "spider-1": "assets/images/spider-1.png",
    
    "blood": "assets/images/blood.png",
    
    "bullet": "assets/images/bullet.png",
    "rocket": "assets/images/rocket.png",  
    "bg": "assets/images/bg.png",    
      
}

sound_paths = {
    
    "shoot": "assets/audio/shoot.wav",
    "theme": "assets/audio/theme.wav",
    "game_won": "assets/audio/game_won.wav",
    "game_over": "assets/audio/game_over.wav",

    
}



from enum import Enum
class GunMovement(Enum):
    LEFT = False
    RIGHT = False
    UP = False
    DOWN = False
    STOP = True