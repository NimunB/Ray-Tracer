-- A simple scene with 3 cylinders

stars_mat = gr.image_material("stars.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)
mat1 = gr.material({0.7, 1.0, 0.7}, {0.5, 0.7, 0.5}, 25, 0)
mat2 = gr.material({0.0, 0.87, 2.1}, {0.5, 0.7, 0.5}, 25, 0) -- blue
sunset_mat = gr.image_material("sunset.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)

checked_mat = gr.image_material("checked.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)
brick_mat = gr.image_material("brick.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)
blackStars_mat = gr.image_material("blackStars.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)

scene_root = gr.node('root')

mat2 = gr.material({0.0, 0.87, 2.1}, {0.5, 0.7, 0.5}, 25, 0) -- blue
mirror1 = gr.mirror_material({0.0, 0.0, 0.0}, {0.8, 0.8, 0.8}, 1000, 0) -- mirror
mirror2 = gr.mirror_material({0.0, 0.0, 0.0}, {0.8, 0.8, 0.8}, 1000, 130) -- mirror

map_mat = gr.image_material("map.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)

pink = gr.material({2.3, 0.8, 1.3}, {0.5, 0.7, 0.5}, 50, 0)

glass = gr.material({0, 0, 0}, {1, 1, 1}, 50000000, 1.5)

waffle = gr.image_material("icecream.png", {1, 1}, {0.0, 0.0, 0.0}, 0, 0)

--centre
s1 = gr.nh_sheet('s1', {0, 0, 0}, 350, 350)
scene_root:add_child(s1)
s1:set_material(mat1)

--left
s2 = gr.nh_sheet('s2', {-175, 0, 0}, 350, 350)
scene_root:add_child(s2)
s2:set_material(brick_mat)
s2:rotate('Y', 90) -- 80
s2:translate(-175, 0, 0)

--right
s3 = gr.nh_sheet('s3', {-175, 0, 0}, 350, 350)
scene_root:add_child(s3)
s3:set_material(brick_mat)
s3:rotate('Y', 90) -- 100
s3:translate(175, 0, 0)

--bottom
s4 = gr.nh_sheet('s4', {-175, 0, 0}, 350, 350)
scene_root:add_child(s4)
s4:set_material(checked_mat)
s4:rotate('Y', 90)
s4:rotate('Z', -90)
s4:translate(0, -175, 0)

--top
s5 = gr.nh_sheet('s5', {-175, 0, 0}, 350, 350)
scene_root:add_child(s5)
s5:set_material(blackStars_mat)
s5:rotate('Y', 90)
s5:rotate('Z', -90)
s5:translate(0, 175, 0)

-- CONE
n1 = gr.nh_cone('n1', {0, 0, 0}, 0)
scene_root:add_child(n1)
n1:rotate('X', 200)
n1:scale(45, 60, 45)
n1:set_material(sunset_mat)
n1:translate(0, -120, 300)

-- cylinder left front
c1 = gr.nh_cylinder('c1', {0, 0, 0}, 0)
scene_root:add_child(c1)
c1:rotate('X', 5)
c1:scale(25, 50, 25)
c1:translate(-100, -120, 300)
c1:set_material(mat2)

b1 = gr.nh_sphere('b1', {0, 0, 0}, 30)
b1:translate(-100, -40, 300)
b1:set_material(mirror2)
scene_root:add_child(b1)

-- cylinder left back
c2 = gr.nh_cylinder('c2', {0, 0, 0}, 0)
scene_root:add_child(c2)
c2:rotate('X', 5)
c2:scale(25, 50, 25)
c2:translate(-50, -120, 170)
c2:set_material(mat2)

b2 = gr.nh_sphere('b2', {0, 0, 0}, 40)
b2:translate(-50, -30, 170)
b2:set_material(pink)
scene_root:add_child(b2)

-- cylinder right back
c3 = gr.nh_cylinder('c3', {0, 0, 0}, 0)
scene_root:add_child(c3)
c3:rotate('X', 5)
c3:scale(25, 50, 25)
c3:translate(50, -120, 170)
c3:set_material(mat2)

b3 = gr.nh_sphere('b3', {0, 0, 0}, 40)
b3:translate(50, -30, 170)
b3:set_material(mirror1)
scene_root:add_child(b3)

-- cylinder right front
c4 = gr.nh_cylinder('c4', {0, 0, 0}, 0)
scene_root:add_child(c4)
c4:rotate('X', 5)
c4:scale(25, 50, 25)
c4:translate(100, -120, 300)
c4:set_material(mat2)

b4 = gr.nh_sphere('b4', {0, 0, 0}, 30)
b4:translate(100, -40, 300)
b4:set_material(map_mat)
scene_root:add_child(b4)

--sphere 1
--[[s6 = gr.nh_sphere('s6', {-100, -105, 175}, 70)
s6:set_material(mirror1)
scene_root:add_child(s6)
--s6:translate(0, 0, 100)

--sphere 2
s7 = gr.nh_sphere('s7', {100, -105, 175}, 70)
s7:set_material(mirror2)
scene_root:add_child(s7)
--s6:translate(0, 0, 100)--]]


scene_root:translate(0, 0, 50)


white_light = gr.light({-100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})
--magenta_light = gr.light({100.0, 150.0, 400.0}, {0.9, 0.9, 0.9}, {1, 0, 0})

gr.render(scene_root, './pictures/FINALSCENE.png', 512, 512,
	  {0, 0, 800}, {0, 0, -800}, {0, 1, 0}, 50,
	  {0.3, 0.3, 0.3}, {white_light})
