# asm-gen
assemply macro generator is a c++ program that I made to genrate easly assemply macro that draw desired shape

The idea was generating my macro files that contain how duck and osbtacle is drawn.
the program can have more features in future and it is code maintanable.


How to use:
1- You get a screenshot of whatever you want to draw
2- Open paint and using grid view and maximum zoom, you can see each pixel in rectangle
3- Divide the shape into rectangles like picture in that directory
4- In paint status bar, you can find the pixel coordinates
5- Just get theses vertices of your rectangles into the code like in load_vertices function in source code
6- And you can scale your shape or reflect or implement others if you want
7- Then you should extend from the base class asmShape and implement generateDrawingasm
