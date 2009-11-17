local cabo = {-15,-15,-15,-15+10}
local cabo2 = {-15+1,-15+1,-15+1,-15+10+1}
local cano = {-15,-15+10,-45,-15+10}
local cano2 = {-15+1,-15+10+1,-45+1,-15+10+1}

math.randomseed( os.time() )

function randomspread(spread)
	return math.random()*2*spread-spread 
end

shotgun = Weapon{
			name = "Shotgun2",
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
								sprite = {
										Line{0,0,1,1},
										}
								}
						end
					   end
}

flamethrower = Weapon{
			name = "Shotgun",
			righthand = {15,-15},
			lefthand = {30,-15+10},
			tip = {-45,-15+10},
			firerate = 60,
			sprite = {
					Line{-15,-15,-15,-15+10},
					Line{-15,-15+10,-45,-15+10},
					Line{-60,-15+5,-60,-15+15},
					},
			whenfire = function (x,y,angle,w)
						local flamesprite = {
											Line{0,0,0,10},
											Line{0,10,10,10},
											Line{10,10,10,0},
											Line{10,0,0,0},
											}
						for i = 1,math.random(7) do
							Shot {
								x = x,
								y = y,
								angle = angle+randomspread(0.2),
								weapon = w,
								speed = 5,
								duration = 1000+math.random(1000)-500,
								gravity = -0.12,
								sprite = flamesprite,
								}
						end
					   end
}

