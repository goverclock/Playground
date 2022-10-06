package main

import (
	"strconv"
	"unicode"
)

// GetNumber
// return (number value, position of next '[')
func getNumber(s string) (int, int) {
	num := ""
	for i, v := range(s) {
		if unicode.IsDigit(rune(v)) {
			num += string(v)
			continue
		}
		ret, _ := strconv.Atoi(num)
		return ret, i
	}
	return -1, -1
}

// findRight
// s begins with '['
// return position of its matching ']'
func findRight(s string) int {
	leftCnt := 0
	for i, v := range(s) {
		if v == rune('[') {
			leftCnt++
		} else if v == rune(']') {
			leftCnt--
		}
		if leftCnt == 0 {
			return i
		}
	}
	return -1
}

func decodeString(s string) string {
	ans := ""
	n := len(s)

	for i := 0; i < n; i++ {
		if unicode.IsLetter(rune(s[i])) {
			ans += string(s[i])
			continue
		}
		// encounter a number
		k, p := getNumber(s[i:])
		r := findRight(s[i+p:])
		dupliSubstr := decodeString(s[i + p + 1:r + i + p])
		for k != 0 {
			ans += dupliSubstr
			k--
		}
		i += p + r
	}

	return ans
}

func main() {
	s := "2[abc]3[cd]ef"
	decodeString(s)
	// fmt.Println(getNumber(s))
	// fmt.Println(findRight(s))
}
