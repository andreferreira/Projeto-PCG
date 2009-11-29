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
			righthand = {-30,-15+10},
			lefthand = {-15,-15},
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


local rainbowcolors = {{221,0,0},
					   {254,98,48},
					   {254,246,0},
					   {0,188,0},
					   {0,155,254},
					   {0,0,131},
					   {48,0,155}}
for i = 1,7 do
	rainbowcolors[i][1] = rainbowcolors[i][1]/255
	rainbowcolors[i][2] = rainbowcolors[i][2]/255
	rainbowcolors[i][3] = rainbowcolors[i][3]/255
end

local rainbowsprite = {}
local rainbowsegments = 40
local rainbowsize = 400
local rainbowheight = 50
for i = 1, rainbowsegments do
	for j = 1,7 do
		rainbowsprite[#rainbowsprite+1] = Line{
								(i/rainbowsegments)*rainbowsize,
								math.sin((i/rainbowsegments)*math.pi)*-rainbowheight+j,
								((i+1)/rainbowsegments)*rainbowsize,
								math.sin(((i+1)/rainbowsegments)*math.pi)*-rainbowheight+j,
								color = rainbowcolors[j],
								}
	end
end


rainbow = Weapon{
		name = "Flamethrower",
		righthand = {10,-30},
		lefthand = {30,-10},
		tip = {-10,15},
		firerate = 1000,
		sprite = {},
		whenfire = function (x,y,angle,w)
					local peitox = math.cos(angle)*x-math.sin(angle)*y --desfaz todo o calculo que eh feito pra ajuste de tip... mas vale apena :D
					local peitoy = math.sin(angle)*x+math.cos(angle)*y
					local s = {}
					local dir = 1
					local add = 0
					if math.abs(angle) < math.pi/2 then
						dir = -1
						add = 17
					end
					for i = 1, #rainbowsprite do
						s[i] = Line {
									rainbowsprite[i][1]*dir+add,
									rainbowsprite[i][2],
									rainbowsprite[i][3]*dir+add,
									rainbowsprite[i][4],
									color = rainbowsprite[i].color
								}
					end
					Shot {
						x = peitox,
						y = peitoy, 
						angle = 0,
						weapon = w,
						speed = 0,
						duration = 600,
						sprite = s,
					}
					end
}

local t = 0
flamethrower = Weapon{
			name = "Flamethrower2",
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
						red = {math.random()/4+0.75,math.random()/3,0}
						for i = 1,math.random(4) do
							local flametip = math.random()*4
							local flamesprite = {mulXY(3,4,
											Line{flametip,0,0,2,color = red},
											Line{0,2,0,3,color = red},
											Line{0,3,1,4,color = red},
											Line{1,4,3,4,color = red},
											Line{3,4,4,3,color = red},
											Line{4,3,4,2,color = red},
											Line{4,2,flametip,0,color = red}
											)}
							t = t + 0.4
							Shot {
								x = x,
								y = y,
								angle = angle+math.sin(t)*0.6+randomspread(0.4),
								weapon = w,
								speed = 3,
								duration = 500+math.random(500)-250,
								gravity = -0.04,
								sprite = flamesprite,
								}
						end
					   end
}

