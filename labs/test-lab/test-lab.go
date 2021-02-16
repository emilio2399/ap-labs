package main

import (
	"fmt"
	"os"
)

func main() {
  if (len(os.Args) < 2) {
  	fmt.Println("Error, no arguments") 
  	} else {
  	  i:= 1
  	  msg:= ""
  	  
  	  for i<len(os.Args){
  	    if i ==1 {
  	      msg=msg + os.Args[i]
  	    }else{
  	      msg=msg + " " + os.Args[i]
  	    }
  	    i++;
  	  }
  	  
      fmt.Println("Hello " +msg+ ", Welcome to the jungle")
  	}
  	
  
}