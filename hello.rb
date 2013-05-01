# puts "Hello World!"
# puts 4+5
# var1 = 'I like ' + 'apple pie.'
# puts var1.reverse 
# puts var1.length
# puts var1.upcase
# puts var1.downcase
# 10.times do
#     puts "Ruby Rocks!"
# end

# var2 = 3
# var3 = '4'
# 
# puts var2.to_s + var3
# puts var2 + var3.to_i
# 
# puts 9.to_f / 2
# Foo = 2
# ENV
# 
# puts nil.nil?
# puts 42.nil?
# 
# a = [1, "cat", 3.14]
# puts a[0]
# puts a.size
# puts a.inspect
# a[2] = nil
# puts a.inspect
# 
# colors = ["red", "blue"]
# colors.push("black")
# colors << "whilte"
# puts colors.join("---")
# 
# colors.pop
# puts colors.last
# puts colors.join(' ')
# 
# config = {"foo" => 123, "bar" => 456}
# puts config["foo"]
# 
# config = { :foo => 123, :bar => 456 }
# puts config[:foo]
# 
# puts ( 2 > 1 ) && ( 2 > 3 ) 
# puts ( 2 > 1 ) || ( 2 > 3 )
# 
# 
# x = 3
# puts ( x > 3 ) ? "large then three" : "smaller then 3"
# 
# name = "Yida"
# case name
#     when "John"
#         puts "Howdy John!"
#     when "Ryan"
#         puts "Whats up Ryan!"
#     else
#         puts "Hi #{name}!"
# end
# 
# i = 0
# while ( i < 10)
#     i += 1
#     next if i % 2 == 0 # skip even number
#     puts i
# end
# 
# i = 0
# loop do
#     i += 1
#     break if i > 10
#     puts i
# end

phone = "857-205-2984"
if phone =~ /(\d{3})-(\d{3})-(\d{4})/
    ext = $1
    city = $2
    num = $3
    puts ext
    puts city
    puts num
end

def say_hello(name)
    result = "Hi, " + name
    return result
end

puts say_hello("Yida")

# class Person
#     def initialize(name)
#         @name = name
#     end
#     def say(word)
#         puts "#{word}, #{@name}"
#     end
# end
# 
# p1 = Person.new("ihower")
# p2 = Person.new("ihover")
# 
# p1.say("hello")
# p2.say("hello")
#
#class Person
#    @@name = "ihower"
#    def self.say
#        puts @@name
#    end
#end
#
#Person.say
#
#class Pet 
#    attr_accessor :name, :age
#end
#
#class Cat < Pet
#end
#
#class Dog < Pet
#end
#
#puts Cat.name
#
#module MyUtil
#    def self.foobar
#        puts "foobar"
#    end
#end
#
#MyUtil.foobar
#
#
#module Debug
#    def who_am_i?
#        "#{self.class.name} (\##{self.object_id}): #{self.to_s}"
#    end
#end
#
#class Foo
#    include Debug
#    def initialize(name)
#        @name = name
#    end
#
#end
#
#class Bar
#    include Debug
#    def initialize(name)
#        @name = name
#    end
#end
#
#ph = Foo.new("123423423")
#et = Bar.new("4320789789")
#ph.who_am_i?
#et.who_am_i?
#
#
#languages = ["ruby", "javascript", "perl"]
#languages.each do |lang|
#    puts "I Love " + lang + "!"
#end
#
#1.upto(9) { |x| puts x }
#
#a = [ "a", "b", "c", "d" ]
#b = a.map { |x| x + "!"}
#puts b.inspect

# b = [1, 2, 3].find_all{ |x| x % 2 == 0 }
# puts b.inspect
# 
# a = [ "a", "b", "c" ]
# a.delete_if { |x| x >= "b" }
# puts a.inspect
# 
# 
# c = [2, 1, 3]
# # c.sort! { |a,b| b <=> a }
# puts c.sort!.inspect
# 
# (5..10).inject { |sum, n| sum + n }
# longest = ["cat", "sheep", "bear"].inject do |memo, word|
#     ( memo.length > word.length) ? memo : word
# end
# puts longest
# 
# File.open("Dropbox/data/gps-csv-04.25.2013.16.02.41-0.csv", 'r') do |file|
#     puts file.inspect
# end
# 
# def call_block
#     puts "Start"
#     yield(1)
#     yield(2)
#     puts "End"
# end
# 
# call_block { |i| puts "#{i} Blocks are cool!" }

def call_block(&block)
    block.call(1)
    block.call(2)
    block.call(3)
end

call_block { |i| puts "#{i}: Blocls are cool!"}

proc_1 = Proc.new { |i| puts "#{i}: Blocks are coool!" }
proc_2 = lambda { |i| puts "#{i}: Blocks are cooool!" }

call_block(&proc_1)
call_block(&proc_2)

def my_sum(*val)
    val.inject(0) { |sum, v| sum + v }
end

puts my_sum(1,2,3,4)
