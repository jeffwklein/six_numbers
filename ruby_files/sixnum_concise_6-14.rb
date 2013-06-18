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
  permute(nums).each do |arr|
    $operators.each do |op|
      new_arr = operation op, arr
      (puts $steps or exit) if new_arr[0] == $target 
      solve new_arr if new_arr.length > 1
      $steps.pop
    end
  end
end

def permute(nums) 
  permutations = nums.combination(2).to_a
  permutations.each do |c|
    c.reverse! if c[1] > c[0]
    nums.select { |x| x != c[0] && x != c[1] }.each { |x| c << x }
  end
  return permutations
end

def operation(sym, nums)
  (sym == "-" and nums[0] == nums[1]) or (sym == "/" and (nums[0] % nums[1]) > 0) and $steps << "" and return[0]
  new_arr = [] << eval("nums[0] #{sym} nums[1]")
  nums.drop(2).each { |x| new_arr << x }
  $steps << "#{nums[0]} #{sym} #{nums[1]} = #{new_arr[0]}"
  return new_arr
end

solve six_numbers
