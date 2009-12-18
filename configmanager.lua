function config(t)
	for i, s in pairs(t.screen) do
		regscreen(i, s)
	end
	
	regplayer("speed", t.player.speed[1], t.player.speed[2])
	regplayerhp("hp", t.player.hp)
	
	for i, m in pairs(t.maps) do
		regmap(m)
	end
	
	return t
end
