//SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.0;

contract StudentData {
    struct Student {
        string name;
        uint rollno;
    }

    Student[] public studentArr;
    // Event to log student data when added
    event StudentAdded(string name, uint256 rollNumber);

    // Event to log Ether received in the fallback function
    event FallbackCalled(address sender, uint256 amount, string message);

    function addStudent(string memory name, uint rollno) public {
        for (uint i = 0; i < studentArr.length; i++) {
            if (studentArr[i].rollno == rollno) {
                revert("Student with roll no already exists!");
            }
        }
        studentArr.push(Student(name, rollno));
        // Emit an event to log the new student addition
            emit StudentAdded(name, rollno);
    }

    function displayAllStudents() public view returns (Student[] memory) {
        return studentArr;
    }

    function getStudentByIndex(
        uint index
    ) public view returns (Student memory) {
        require(
            index < studentArr.length || index > studentArr.length,
            "Index out of bound"
        );
        return studentArr[index];
    }

    function getLengthOfStudents() public view returns (uint) {
        return studentArr.length;
    }

    //fallbacks
    fallback() external payable {
        //This function will handle external function calls that is not there in our contract
        revert("This function does not exist");
    }
    receive() external payable {
        //This function will handle the native token transfer to our contract
        revert("This function does not exist");
    }
   
}
