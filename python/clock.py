# Get the angle between two clock handles

degreePerMark = 360 / 60

hour = 14
min = 30

minAngle = min * degreePerMark
hourAngle = hour * 5 * degreePerMark

angle = 360 - abs(hourAngle - minAngle)

print(angle)
