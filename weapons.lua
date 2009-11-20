local cabo = {-15,-15,-15,-15+10}
local cabo2 = {-15+1,-15+1,-15+1,-15+10+1}
local cano = {-15,-15+10,-45,-15+10}
local cano2 = {-15+1,-15+10+1,-45+1,-15+10+1}

math.randomseed( os.time() )

function randomspread(spread)
	return math.random()*2*spread-spread 
end

shotgun = Weapon{
			name = "Shotgun",
			righthand = {-15,-15},
			lefthand = {-30,-15+10},
			tip = {-45,-15+10},
			firerate = 1000,
			sprite = {
					Line(cabo),
					Line(cabo2),
					Line(cano),
					Line(cano2)},
			whenfire = function (x,y,angle,w)
						for i = 1,5 do
							Shot {
								x = x,
								y = y,
								angle = angle+randomspread(0.2),
								weapon = w,
								duration = 1000,
								speed = 4,
								sprite = {
										Line{0,0,3,0},
										Line{3,0,3,3},
										Line{3,3,0,3},
										Line{0,3,0,0},
										}
								}
						end
					   end
}

function addXY(x,y,...)
	local t = {...}
	for i = 1, #t do
		t[i][1] = t[i][1] + x
		t[i][2] = t[i][2] + y
		t[i][3] = t[i][3] + x
		t[i][4] = t[i][4] + y
	end
	return unpack(t)
end

function mulXY(x,y,...)
	local t = {...}
	for i = 1, #t do
		t[i][1] = t[i][1] * x
		t[i][2] = t[i][2] * y
		t[i][3] = t[i][3] * x
		t[i][4] = t[i][4] * y
	end
	return unpack(t)
end

flamethrower = Weapon{
			name = "Shotgun2",
			righthand = {-20,-13},
			lefthand = {-25,-10},
			tip = {-65,-15+10},
			firerate = 60,
			sprite = {addXY(-10,0,
					Line{-20,-15,-20,-15+10},
					Line{-20,-15,-35,-15},
					Line{-35,-15,-35,-15+10},
					Line{-5,-15,-15,-15+10},
					Line{-5-8,-15+8,-5-8,-15},
					Line{-15,-15+10,-50,-15+10},
					Line{-40,-15+10,-50,-15},
					Line{-50,-15,-65,-15},
					Line{-65,-15,-65,-10},
					Line{-60,-15+6,-60,-15+13},
					Line{-50,-15+6,-60,-15+6},
					Line{-50,-15+13,-60,-15+13},
					Line{-50,-15+6,-50,-15+13}
					)
					},
			whenfire = function (x,y,angle,w)
						for i = 1,math.random(4) do
							local flametip = math.random()*4
							local flamesprite = {mulXY(3,4,
											Line{flametip,0,0,2},
											Line{0,2,0,3},
											Line{0,3,1,4},
											Line{1,4,3,4},
											Line{3,4,4,3},
											Line{4,3,4,2},
											Line{4,2,flametip,0}
											)}
							Shot {
								x = x,
								y = y,
								angle = angle+randomspread(0.6),
								weapon = w,
								speed = 2,
								duration = 500+math.random(500)-250,
								gravity = -0.03,
								sprite = flamesprite,
								}
						end
					   end
}

