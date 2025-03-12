/*------------------------------------------------------------------------------
 *  This file is part of a small RayTracer code, that is used in the course
 *  Scientific Computing for Mechanical Engineering (4EM30) at the Department
 *  Mechanical Engineering at Eindhoven University of Technology.
 *
 *  (c) 2020-2022 Joris Remmers, TU/e
 *
 *  Versions:
 *  05/01/2022 | J.Remmers    | First version
 *             |              |
 *----------------------------------------------------------------------------*/
 
The BMW model files are obtained from the repository of the Physics Based 
Rendering code, https://github.com/mmp/pbrt-v4. See BLENDSWAP_LICENSE.txt 
for further details.

================================================================================

bmw_m6.in      

Description:

Full model of a BMW M6 (2006) car. In order to reduce the model, only the 
left front wheel is detailed (the other weels do not have a caliper or 
brake disc).

Resolution:         300x400 px

Number of faces:    390358

Number of spheres:  1

Approximate runtime with original code:  

- 4000 sec. (Ubuntu linux, Intel Core I7 processor)

================================================================================

bmw_bodywork.in      

Description:

Hi resolution model of the bodywork of the BMW M6 car.

Resolution:         300x400 px

Number of faces:    64874

Number of spheres:  1

Approximate runtime with original code:  

- 700 sec. (Ubuntu linux, Intel Core I7 processor)

================================================================================

wheel.in

Description:

A high resolution model of a wheel (rim, tyre, brake disc and caliper) in order 
to test the performance of the raytracer code. The model is a detail of the 
large BMW M6 model.

Resolution:         300x400 px

Number of faces:    60079

Number of spheres:  7

Approximate runtime with original code:  

- 650 sec. (Ubuntu linux, Intel Core I7 processor)

================================================================================

wheel_lo.in      

Description:

A low resolution model of a wheel (rim and tyre) in order to test the 
performance of the raytracer code. The tyre profile, brake disc and brake 
caliper have been removed.

Resolution:         300x400 px

Number of faces:    22530

Number of spheres:  7

Approximate runtime with original code:  

- 250 sec. (Ubuntu linux, Intel Core I7 processor)

================================================================================

bmw_m6_original.in

Description:

The vertices and faces of the original BMW M6 model. This file only contains
the vertices and faces data.

================================================================================

bmw_m6_background.in

Description:

The background for the BMW M6. This file only contains the vertices and 
faces data.

================================================================================
