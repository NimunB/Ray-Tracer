-- [[You should place your test scene in a file called sample.lua in the A4 directory. 
-- The test scene should contain at least one of each required primitive type, 
-- at least one point light source, 
-- at least one shiny surface (with obvious specular reflection), 
-- a non-trivial background (see below) and 
-- at least one demonstration of your additional feature. The script should produce a rendered image in sample.png and exit. ]]--

mat1 = gr.material({2.3, 0.8, 1.3}, {0.5, 0.7, 0.5}, 50) -- pink
mat2 = gr.material({0.0, 0.87, 2.1}, {0.5, 0.7, 0.5}, 25) -- blue
mat3 = gr.material({0.0, 1.0, 0.0}, {0.5, 0.7, 0.5}, 25) -- green

scene_root = gr.node('root')

s1 = gr.nh_sphere('s1', {-400, -400, -400}, 50)
scene_root:add_child(s1)
s1:set_material(mat1)

s2 = gr.nh_sphere('s2', {-275, -275, -300}, 75)
scene_root:add_child(s2)
s2:set_material(mat2)


s3 = gr.nh_sphere('s3', {-125, -125, -200}, 100)
scene_root:add_child(s3)
s3:set_material(mat1)

s4 = gr.nh_sphere('s4', {75, 75, -100}, 140)
scene_root:add_child(s4)
s4:set_material(mat2)

s5 = gr.nh_box('s5', {75, -175, -100}, 70)
scene_root:add_child(s5)
s5:set_material(mat3)

b1 = gr.nh_box('b1', {200, 225, -100}, 80)
scene_root:add_child(b1)
b1:set_material(mat3)

b2 = gr.nh_box('b2', {-30, 180, 100}, 80)
scene_root:add_child(b2)
b2:set_material(mat3)

--[[
-- s4 = gr.nh_sphere('s4', {-100, 25, -300}, 50)
s4 = gr.nh_sphere('s4', {-150, -085, 150}, 30)
scene_root:add_child(s4)
s4:set_material(mat1)

s5 = gr.nh_sphere('s5', {0, 100, -250}, 25)
scene_root:add_child(s5)
s5:set_material(mat2)
--]]
white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
yellow_light = gr.light({100.0, 500.0, 500.0}, {0.7, 0.0, 0.7}, {1, 0, 0})

gr.render(scene_root, 'sample.png', 512, 512,
	  {0, 0, 800}, {0, 0, -1}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light, yellow_light})