$steps = []
numbers = []
print "Enter target number: "
$target = gets.chomp.to_i
6.times do |i|
  print "Enter number #{i+1}: " 
  numbers << gets.chomp.to_i
end

def permute(nums) 
  permutations = nums.combination(2).to_a
  permutations.each do |c|
    c.reverse! if c[1] > c[0]
    nums.select { |i| i != c[0] && i != c[1] }.each { |i| c << i }
  end
  return permutations
end

def solve(nums)
  if nums.length > 1
    perms = permute(nums)
    perms.each do |arr|
      4.times do |i|
        new_arr = []
        if i == 0
          new_arr = add(arr)
        elsif i == 1
          new_arr = subtract(arr)
        elsif i == 2
          new_arr = multiply(arr)
        elsif i == 3
          new_arr = divide(arr)
        end
        finish(new_arr) if new_arr[0] == $target
        solve(new_arr)
        $steps.pop
      end
    end
  end
end

def add(nums)
  new_arr = [] << (nums[0] + nums[1])
  nums.drop(2).each { |x| new_arr << x }
  $steps << "#{nums[0]} + #{nums[1]} = #{new_arr[0]}"
  return new_arr
end

def subtract(nums)
  nums[0] == nums[1] and $steps << "" and return [0] 
  new_arr = [] << (nums[0] - nums[1])
  nums.drop(2).each { |x| new_arr << x }
  $steps << "#{nums[0]} - #{nums[1]} = #{new_arr[0]}"
  return new_arr
end

def multiply(nums)
  new_arr = [] << (nums[0] * nums[1])
  nums.drop(2).each { |x| new_arr << x }
  $steps << "#{nums[0]} * #{nums[1]} = #{new_arr[0]}"
  return new_arr
end

def divide(nums)
  (nums[0] % nums[1]) > 0 and $steps << "" and return [0]
  new_arr = [] << (nums[0] / nums[1])
  nums.drop(2).each { |x| new_arr << x }
  $steps << "#{nums[0]} / #{nums[1]} = #{new_arr[0]}"
  return new_arr
end

def finish(nums)
  puts $steps
  exit
end

solve numbers
