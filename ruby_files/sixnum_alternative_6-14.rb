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
  permute(nums).each { |arr| $operators.each { |op| (arr.length == 1 or (solve(operation(op, arr)) and $steps.pop)) or true} }
end

def permute(nums) 
  return nums.combination(2).to_a.each { |c| ((c.reverse! if c[1] > c[0]) or true) and nums.each { |x| x != c[0] && x != c[1] and c << x } }
end

def operation(sym, nums)
  new_arr = []
  str = str2 = ""
  n = 0
  ((sym == "-" and nums[0] == nums[1]) or (sym == "/" and (nums[0] % nums[1]) > 0) and $steps << "" and return[0]) or (($steps << (str += " = " + ((new_arr << n = eval(str2 = "#{nums[0]} #{sym} #{nums[1]}")).concat(nums.drop(2)))[0].to_s).insert(0,str2)) and n == $target and (puts $steps or exit))
  new_arr
end

solve six_numbers
