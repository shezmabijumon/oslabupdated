
temp=$1
sum=0
reverse=0
while [[ $temp -gt 0 ]] ; do
    d=$((temp%10))
    sum=$((sum+d))
    reverse=$((reverse*10+d))
    temp=$((temp/10))
done
echo "Sum of digits: $sum"
echo "Reverse : $reverse"
