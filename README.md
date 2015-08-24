# Soft body dynamics

This project was created to aid a research project I did at Petnica science center (http://www.petnica.rs/), during the summer of 2012, between the end of high school and start of university.

The goal of the research was to create a soft body behavior model that would be sufficiently simple to simulate in real tme. The goal was to achieve visually satisfying behavior, not physical accuracy.

The resulting simulation is demostrated in a youtube video:

<a href="http://www.youtube.com/watch?feature=player_embedded&v=2jkwMjSY5fI
" target="_blank"><img src="http://img.youtube.com/vi/2jkwMjSY5fI/0.jpg" 
alt="IMAGE ALT TEXT HERE" width="240" height="180" border="10" /></a>

The main aproach taken was to represent each soft body as a mesh of point masses (analogous to the real world) and to introduce springs between them to simulate intermolecular forces.

The boundary of the soft bodies is made of quadratic bezier curves, more specifically in this case they behave like oriented parabolas. The amount of "bend" of each curve is related to the compression of the underlying boundary spring.

The project also allows the procedural construction of arbitrary soft bodies, and the corresponding mesh of springs which is a triangulation problem. In this project an algorithm similar to the Delaunay triangulation was developed (although it has a worse asymptotic running time, it was an exercise in algorithm construction).

The result of the project is a paper on soft body physics that was published in the 2012 Petnica science center students' projects journal, ISBN: 978-86-7861-049-3.

The paper (most of it is in serbian) is available in [PDF](sbp2012.pdf).

##Dependencies, compilation
The only library needed to compile this is [libsdl1.2-dev](https://www.libsdl.org/download-1.2.php). For compilation just use the makefile.

##Instructions

Run the application from the console. 

###Creating the shape
1. Draw an outline of the soft body above the purple lines, with consecutive left cliks.
2. Press ENTER.

###Controls
- Middle mouse (wheel) click: Reposition the shape.
- Right mouse button: toggle between elasticity changing or damping changing.
- Mouse wheel up/down: increase/decrease elasticity or damping depending on which is active (see above^).
- Left/Right arrow: rotate boundary.
