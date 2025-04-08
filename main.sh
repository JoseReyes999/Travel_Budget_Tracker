printf "Welcome to your travel budget assistant.\n"

hasTrip=false

if [ "$hasTrip" = true]; then
  echo "You already have trips"
else
  echo "You have to create a new trip"
fi

printf ""

printf "What do you want me to do\n1. Add to your budget\n2. Add expense\n3. View history\n"

