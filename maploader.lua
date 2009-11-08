function map(t)
	regmap(t.width,t.height)
	for i,p in pairs(t.platforms) do
		regplatform(p[1],p[2],p[3],p[4],p[5])
	end
	return t
end

function platform(t)
	if t[5] == nil then
		t[5] = true
	end
	return t
end
