-- A simple scene with 3 cylinders

stars_mat = gr.image_material("stars.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)
sunset_mat = gr.image_material("sunset.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)
mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0)
mat4 = gr.material({1.0, 0.6, 1.0}, {0.5, 0.7, 0.5}, 25, 0)

scene_root = gr.node('root')

--cylinder
s1 = gr.nh_cylinder('s1', {0, 0, 0}, 0)
scene_root:add_child(s1)
s1:rotate('X', 20)
s1:scale(90, 90, 90)
s1:set_material(mat1)

--sphere
s2 = gr.nh_sphere('s2', {0, 0, 0}, 90, 90)
s2:set_material(mat1)
scene_root:add_child(s2)
s2:translate(-230, 0, 0)

--cone
s3 = gr.nh_cone('s3', {0, 0, 0}, 0)
scene_root:add_child(s3)
s3:rotate('X', 160)
s3:scale(100, 100, 100)
s3:set_material(mat1)
s3:translate(230, 50, 0)


--scene_root:translate(0, 0, 50)

--[[s4 = gr.nh_sheet('s4', {0, 0, 0}, 350, 350)
scene_root:add_child(s4)
s4:set_material(mat1)
s4:translate(0, 0, -175)
s4:rotate('X', 110)--]]

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
--magenta_light = gr.light({100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, './pictures/reflection.png', 512, 512,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})
