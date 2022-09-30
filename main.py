import turtle
t = turtle.Turtle()
s = turtle.Screen()
s.bgcolor('black')
t.pencolor('red')
t.speed()
color = ('cyan', 'green', 'white', 'yellow', 'blue', 'pink', 'red')
for n in range(0, 8):
    for x in range(8):
        t.speed(x+10)
        for i in range(2):
            t.pensize(2)
            t.circle(80+n*20, 90)
            t.lt(90)
        t.lt(45)
    t.pencolor(color[n%5])
s.exitonclick()