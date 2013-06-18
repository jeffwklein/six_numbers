$steps = []
$operators = ["+", "-", "*", "/"]
six_numbers = []
print "Enter target number: "
$target = gets.chomp.to_i
6.times do |i|
  print "Enter number #{i+1}: "
  six_numbers << gets.chomp.to_i
end

def solve(nums)
  permute(nums).each { |arr| $operators.each { |op| (new_arr = operation(op, arr))[0] == $target and (puts $steps or exit) or (new_arr.length > 1 and solve new_arr) or true and $steps.pop } }
end

def permute(nums) 
  return nums.combination(2).to_a.each { |c| ((c.reverse! if c[1] > c[0]) or true) and nums.each { |x| x != c[0] && x != c[1] and c << x } }
end

def operation(sym, nums)
  ((sym == "-" and nums[0] == nums[1]) or (sym == "/" and (nums[0] % nums[1]) > 0) and $steps << "" and return[0]) or (new_arr = [] << eval(s = "#{nums[0]} #{sym} #{nums[1]}") and nums.drop(2).each { |x| new_arr << x } and $steps << s + " = #{new_arr[0]}" and return new_arr)
end

solve six_numbers
