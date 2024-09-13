SCREEN_WIDTH = 800
SCREEN_HEIGHT = 600

SPIDER_WIDTH = 100
SPIDER_HEIGHT = 150
SPIDER_MAX_FUEL = 10 # 10 bullets
SPIDER_VELOCITY = [5, 5]  
SCREEN_BOUNDS = [-SCREEN_WIDTH//2, SCREEN_WIDTH, -SCREEN_HEIGHT//2, SCREEN_HEIGHT//2]  # [left, right, bottom, top]

GUN_WIDTH = 150
GUN_HEIGHT = 200
GUN_MOVE_X_VELOCITY = 10
GUN_MOVE_Y_VELOCITY = 5
GUN_MAX_UP_POSITION =-(SCREEN_HEIGHT//2 -100)
GUN_MAX_DOWN_POSITION = -(SCREEN_HEIGHT//2 +50)


BULLET_WIDTH = 20
BULLET_HEIGHT = 40
BULLET_VELOCITY = 10 


GROUND_STARTING_HEIGHT_GUN = 0
GROUND_STARTING_HEIGHT_SPIDER = 0



image_paths={
    "spider-injured": "assets/images/spider-injured.png",
    "spider-0": "assets/images/spider-0.png",
    "spider-1": "assets/images/spider-1.png",
    
    "blood": "assets/images/blood.png",
    
    "bullet": "assets/images/bullet.png",
    "rocket": "assets/images/rocket.png",    
}

music_paths = {
    "shoot": "assets/audio/shoot.wav",
}



from enum import Enum
class GunMovement(Enum):
    LEFT = False
    RIGHT = False
    UP = False
    DOWN = False
    STOP = True