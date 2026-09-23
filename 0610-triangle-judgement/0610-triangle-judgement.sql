SELECT 
x,y,z,
case when x + y > z and y + z > x and z + x > y then 'Yes' else 'No' end
AS triangle
FROM Triangle