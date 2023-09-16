-- A simple scene with 3 cylinders

stars_mat = gr.image_material("stars.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)
sunset_mat = gr.image_material("sunset.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)
mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25, 0)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25, 0)

map_mat = gr.image_material("map.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)

scene_root = gr.node('root')

--s1 = gr.nh_sheet('s1', {0, 0, -100}, 350, 350)
s1 = gr.nh_sphere('s1', {0, 0, 0}, 256, 256)
scene_root:add_child(s1)
--s1:rotate('Z', 90)
--s1:rotate('X', 90)
--s1:rotate('Y', 70)
s1:set_material(map_mat)


white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, './pictures/sphereTM.png', 512, 512,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})
