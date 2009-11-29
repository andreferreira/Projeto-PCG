function Weapon(t)
	local w = regweapon(t.righthand[1],t.righthand[2],
						t.lefthand[1],t.lefthand[2],
						t.name,t.firerate,
						t.tip[1],t.tip[2])
	regfirefunction(w,t.whenfire)
	for i = 1, #t.sprite do
		regspriteline(w,t.sprite[i][1],t.sprite[i][2],t.sprite[i][3],t.sprite[i][4],
					  t.sprite[i].color[1],t.sprite[i].color[2],t.sprite[i].color[3])
	end
	local minX, minY, maxX, maxY = math.huge, math.huge, -math.huge, -math.huge
	for i = 1, #t.sprite do
		minX = math.min(minX, t.sprite[i][1], t.sprite[i][3])
		minY = math.min(minY, t.sprite[i][2], t.sprite[i][4])
		maxX = math.max(maxX, t.sprite[i][1], t.sprite[i][3])
		maxY = math.max(maxY, t.sprite[i][2], t.sprite[i][4])
	end
	regcollision(t.name, minX, minY, minX, maxY)
	regcollision(t.name, minX, minY, maxX, minY)
	regcollision(t.name, maxX, maxY, minX, maxY)
	regcollision(t.name, maxX, maxY, maxX, minY)		
	return t
end

function Line(t)
	if t.color == nil then
		t.color = {0,0,0}
	end
	return t
end

function default(t,k,v)
	if t[k] == nil then
		t[k] = v
	end
end

function Shot(t)
	default(t,"gravity",0)
	default(t,"duration",3000)
	default(t,"speed",10)
	local s = createshot(t.x,t.y,t.angle,t.duration,t.weapon,t.gravity,t.speed)
	for i = 1, #t.sprite do
		regspritelineshot(s,t.sprite[i][1],t.sprite[i][2],t.sprite[i][3],t.sprite[i][4],
						  t.sprite[i].color[1],t.sprite[i].color[2],t.sprite[i].color[3])
	end
end
