
# Initialize the ball properties
ball_pos = [0, 0]  # [x, y] position of the ball
ball_radius = 0.1  # Radius of the ball
ball_velocity = [0.02, 0.01]  # [vx, vy] velocity of the ball

# Initialize screen boundaries
screen_bounds = [-1, 1, -1, 1]  # [left, right, bottom, top]

def draw_ball():
    """Draw a simple 2D circle (the ball) using OpenGL"""
    glBegin(GL_POLYGON)
    for i in range(20):
        theta = 2.0 * math.pi * i / 20  # Calculate the angle
        x = ball_radius * math.cos(theta)
        y = ball_radius * math.sin(theta)
        glVertex2f(ball_pos[0] + x, ball_pos[1] + y)
    glEnd()

def move_ball():
    """Update ball position and handle boundary collisions"""
    # Move the ball based on its velocity
    ball_pos[0] += ball_velocity[0]
    ball_pos[1] += ball_velocity[1]

    # Check for collisions with screen boundaries
    if ball_pos[0] - ball_radius < screen_bounds[0] or ball_pos[0] + ball_radius > screen_bounds[1]:
        ball_velocity[0] *= -1  # Reverse the x direction
    if ball_pos[1] - ball_radius < screen_bounds[2] or ball_pos[1] + ball_radius > screen_bounds[3]:
        ball_velocity[1] *= -1  # Reverse the y direction
def draw_bar():
    """Draw a simple 2D rectangle (the bar) using OpenGL"""
    glBegin(GL_POLYGON)
    glVertex2f(-0.2, -0.9)
    glVertex2f(0.2, -0.9)
    glVertex2f(0.2, -0.8)
    glVertex2f(-0.2, -0.8)
    glEnd()
    

def main():
    # Initialize Pygame and create an OpenGL window
    pygame.init()
    pygame.display.set_mode((800, 600), DOUBLEBUF | OPENGL)

    # Set the OpenGL projection
    glMatrixMode(GL_PROJECTION)
    glLoadIdentity()
    glOrtho(-1, 1, -1, 1, -1, 1)  # Set the coordinate system

    clock = pygame.time.Clock()
    
    # Main loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == QUIT:
                running = False

                    

        # Clear the screen
        glClear(GL_COLOR_BUFFER_BIT)

        # Move and draw the ball
        move_ball()
        draw_ball()
        # draw_bar()

        # Swap buffers to display the current frame
        pygame.display.flip()

        # Cap the frame rate
        clock.tick(60)

    pygame.quit()

if __name__ == "__main__":
    main()
