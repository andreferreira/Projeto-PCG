local cabo = {-15,-15,-15,-15+10}
local cabo2 = {-15+1,-15+1,-15+1,-15+10+1}
local cano = {-15,-15+10,-45,-15+10}
local cano2 = {-15+1,-15+10+1,-45+1,-15+10+1}

math.randomseed( os.time() )
	
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
							createshot(x,y,angle+math.random()/5-0.1,1000,w)
						end
					   end
}
