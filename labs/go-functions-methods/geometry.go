package main

import (
	"fmt"
	"math"
	"math/rand"
	"os"
	"strconv"
	"time"
)

type Point struct {
	x, y float64
}

func X(p Point) float64 {
	return p.x
}
func Y(p Point) float64 {
	return p.y
}

// traditional function
func Distance(p, q Point) float64 {
	return math.Hypot(X(q)-X(p), Y(q)-Y(p))
}

func (p Point) Distance(q Point) float64 {
	return math.Hypot(X(q)-X(p), Y(q)-Y(p))
}

// A Path is a journey connecting the points with straight lines.
type Path []Point

// Distance returns the distance traveled along the path.
func (path Path) Distance() float64 {
	sum := 0.0
	for i := range path {
		if i > 0 {
			sum += path[i-1].Distance(path[i])
		}
	}
	return sum
}

func createRandom() Point {
	s1 := rand.NewSource(time.Now().UnixNano())
	r1 := rand.New(s1)
	var bin int
	var randTmp, randTmp2 float64

	bin = r1.Intn(2)
	if bin == 0 {
		bin = -1
	}
	randTmp = r1.Float64() * float64(100) * float64(bin)
	bin = r1.Intn(2)
	if bin == 0 {
		bin = -1
	}
	randTmp2 = r1.Float64() * float64(100) * float64(bin)
	return Point{randTmp, randTmp2}
}

func createPoints(sides int) Path {
	var pathList []Point
	var tmpPoint Point
	pathList = append(pathList, createRandom())
	pathList = append(pathList, createRandom())
	pathList = append(pathList, createRandom())
	tries := 0
	for len(pathList) < sides && tries < 50 {

		tmpPoint = createRandom()
		tmpCount := len(pathList) - 2
		flag := false

		for tmpCount > 0 {
			flag = validatePoints(tmpPoint, pathList[len(pathList)-1], pathList[tmpCount], pathList[tmpCount-1])
			if flag {
				tries++

				break
			}
			tmpCount -= 1
		}
		if flag == false {

			if len(pathList) == sides-1 {
				tmpCount2 := len(pathList) - 1
				for tmpCount2 > 1 {
					flag = validatePoints(pathList[0], tmpPoint, pathList[tmpCount2], pathList[tmpCount2-1])
					if flag {

						tries++
						break
					}
					tmpCount2 -= 1
				}
				if flag == false {

					pathList = append(pathList, tmpPoint)
				}
			} else {

				pathList = append(pathList, tmpPoint)
			}
		}
	}
	if sides == 3 {
		if orientation(pathList[0], pathList[1], pathList[2]) == 0 {
			return createPoints(sides)
		} else {
			return pathList
		}
	} else if tries >= 50 {
		return createPoints(sides)
	} else {
		return pathList
	}

}

func onSegment(p, q, r Point) bool {
	if X(q) <= math.Max(X(p), X(r)) && X(q) >= math.Min(X(p), X(r)) &&
		Y(q) <= math.Max(Y(p), Y(r)) && Y(q) >= math.Min(Y(p), Y(r)) {
		return true
	} else {
		return false
	}
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
func orientation(p, q, r Point) int {
	val := (Y(q)-Y(p))*(X(r)-X(q)) - (X(q)-X(p))*(Y(r)-Y(q))

	if val == 0 {
		return 0
	} else if val > 0 {
		return 1
	} else {
		return 2
	}
}

func validatePoints(p1, q1, p2, q2 Point) bool {
	var o1, o2, o3, o4 int
	o1 = orientation(p1, q1, p2)
	o1 = orientation(p1, q1, q2)
	o1 = orientation(p2, q2, p1)
	o1 = orientation(p2, q2, q1)

	if o1 != o2 && o3 != o4 {
		return true
	} else if o1 == 0 && onSegment(p1, p2, q1) {
		return true
	} else if o2 == 0 && onSegment(p1, q2, q1) {
		return true
	} else if o3 == 0 && onSegment(p2, p1, q2) {
		return true
	} else if o4 == 0 && onSegment(p2, q1, q2) {
		return true
	} else {
		return false
	}

}

func main() {
	sides, err := strconv.Atoi(os.Args[1])
	if err != nil {
		fmt.Println("Please write a number")
	}
	if sides < 3 {
		fmt.Println("ERROR Figure must have at least 3 sides")
		//os.Exit(3)
	}
	fmt.Println("Generating a figure with", sides, "sides.")
	finalPoints := createPoints(sides)
	fmt.Println("Figure's vertices:")
	for i := 0; i < sides; i++ {
		fmt.Println(X(finalPoints[i]), ",", Y(finalPoints[i]))
	}

	fmt.Println("Figure's perimeter:")
	fmt.Println(finalPoints.Distance())

}
