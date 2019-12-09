set breakpoint pending on
set confirm off
file ./lakec
break lake::Err::report
commands
	where
end
break lake::ToDoError::ToDoError
commands
	where
end
break lake::InternalError::InternalError
commands
	where
end

define t2
  set args p2_tests/$arg0.lake -p --
  run
end

define t3
  set args p3_tests/$arg0.lake -n --
  run
end

define t4
  set args p4_tests/$arg0.lake -c
  run
end

define t5
  set args p4_tests/$arg0.lake -a --
  run
end
