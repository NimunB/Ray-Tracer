-- A simple scene with 3 cylinders

mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25)
mat2 = gr.material({0.5, 0.5, 0.5}, {0.5, 0.7, 0.5}, 25)
mat3 = gr.material({1.0, 0.6, 0.1}, {0.5, 0.7, 0.5}, 25)
mat4 = gr.material({1.0, 0.6, 0.1}, {0.0, 0.0, 0.0}, 0)

scene_root = gr.node('root')

s1 = gr.nh_cone('s1', {0, 0, 0}, 0)
scene_root:add_child(s1)
s1:rotate('X', 160)
--s1:rotate('X', 20)
--s1:rotate('Y', 45)
--s1:rotate('Z', 45)
s1:scale(50, 50, 50)
s1:set_material(mat1)

white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
magenta_light = gr.light({400.0, 100.0, 150.0}, {0.7, 0.0, 0.7}, {1, 0, 0})

gr.render(scene_root, './pictures/coneB.png', 256, 256,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})
