#include "inputvalidator.h"

#include <QString>
#include <QDebug>

InputValidator::InputValidator() {
    SquareOpen = false;
    PeriodOpen = false;
    PeriodClosed = false;
    WasPoint = false;
    WholePart = false;
    RationalPart = false;
    PeriodPart = false;
    IsNum = false;
    Correct = true;
    curNum = 0;
    Correct = false;
}

void InputValidator::ShowError(std::string message) {
    qDebug() << QString::fromStdString(message);
};

bool InputValidator::InputCheck(std::string input, double p, double q) {
    if (input.size() == 0) {
        ShowError("Input cannot be empty");
        return false;
    }
    int p_copy = p;
    int q_copy = q;
    if (p_copy != p) {
        ShowError("p must be whole number");
        return false;
    }
    if (q_copy != q) {
        ShowError("q must be whole number");
        return false;
    }
    if (p_copy < 2 || p_copy > 500) {
        ShowError("p must be from 2 to 500");
        return false;
    }
    if (q_copy < 2 || q_copy > 500) {
        ShowError("q must be from 2 to 500");
        return false;
    }
    char part = ' ';
    Correct = true;
    SquareOpen = false;
    PeriodOpen = false;
    PeriodClosed = false;
    WasPoint = false;
    WholePart = false;
    RationalPart = false;
    PeriodPart = false;
    IsNum = false;
    Correct = true;
    curNum = 0;
    for (int i = 0; i < input.size(); ++i) {
        part = input[i];
        if (PeriodClosed == true) {
            ShowError("Nothing cannot be after period");
            Correct = false;
            break;
        }
        if(part == ' ') {
            ShowError("The digit cannot contain spaces");
            Correct = false;
            break;
        } else if (part == '[') {
            if (SquareOpen == true) {
                ShowError("The digit into [] cannot contain another digit in []");
                Correct = false;
                break;
            } else {
                SquareOpen = true;
                continue;
            }
        } else if (part == ']') {
            if (IsNum == false) {
                ShowError("The digit cannot be empty");
                Correct = false;
                break;
            } else if (SquareOpen == false) {
                ShowError("The digit has square backet without pair");
                Correct = false;
                break;
            } else {
                if (curNum >= p) {
                    std::string message =
                        "The digit [" + std::to_string(curNum) +
                        "] is invalid for base " +
                        std::to_string(p_copy);

                    ShowError(message);
                    return false;
                }
                SquareOpen = false;
                IsNum = false;
                curNum = 0;
                if (WasPoint == true && PeriodOpen == false) RationalPart = true;
                if (WasPoint == false) WholePart = true;
                if (PeriodOpen == true) PeriodPart = true;
                continue;
            }
        } else if (part == '.') {
            if (SquareOpen == true || PeriodOpen == true) {
                ShowError("The bucket cannot contain dot");
                Correct = false;
                continue;
            }
            if (WholePart == false) {
                ShowError("The Whole part must be before dot");
                Correct = false;
                continue;
            }
            if (WasPoint == true) {
                ShowError("The dot must appear no more than once");
                Correct = false;
                break;
            } else {
                WasPoint = true;
                continue;
            }
        } else if (part == '(') {
            if (SquareOpen == true) {
                ShowError("Square bucket cannot contain period");
                Correct = false;
                break;
            }
            if (WasPoint == false) {
                ShowError("The whole part cannot contain period");
                Correct = false;
                break;
            }
            if (PeriodOpen == true) {
                ShowError("Period cannot contain another period");
                Correct = false;
                break;
            } else {
                PeriodOpen = true;
                continue;
            }
        } else if (part == ')') {
            if (PeriodPart == false) {
                ShowError("Period cannot be empty");
                Correct = false;
                break;
            }
            if (PeriodOpen == false) {
                ShowError("The digit has period without pair");
                Correct = false;
                break;
            }
            PeriodOpen = false;
            PeriodClosed = true;
            continue;
        } else if (part >= '0' && part <= '9') {
            IsNum = true;
            int num = part - '0';
            curNum = curNum * 10 + num;
            continue;
        } else {
            std::string message = "The digit contain invalid symbol " + std::string(1, part);
            ShowError(message);
            Correct = false;
            break;
        }
    }
    if (SquareOpen == true || PeriodOpen == true) {
        ShowError("Buckets cannot be unclosed");
        return false;
    }
    if (WasPoint == true && RationalPart == false && PeriodPart == false) {
        ShowError("The dot cannot be at the and of the digit");
        return false;
    }
    if (WholePart == false) {
        ShowError("The whole part cannot be empty");
        return false;
    }
    return Correct;
}
