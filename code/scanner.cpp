#include "scanner.h"
#include <QMessageBox>
enum STATE { START, INNUM, INID, INASSIGN, INCOMMENT, DONE } state, prev_state;
void vector_print(vector<Token> token_vector)
{

    ofstream output("./output_files/scanner_output.txt",fstream::out);
    for (unsigned int i = 0; i < token_vector.size(); i++) {
        if (token_vector[i].get_type() != "Error" && token_vector[i].get_type() != "Break") {
            output << token_vector[i].value << ", " << token_vector[i].type << endl;

        }
		else if (token_vector[i].get_type() == "Break") {
			return;
		}else {
            output << token_vector[i].value << ", " << token_vector[i].type << endl;
            QMessageBox msgBox;
            msgBox.setText(QString::fromStdString(token_vector[i].value));
            msgBox.exec();
            return;
        }
    }
    output.close();
}

void scan(string file_location)
{
    ifstream code;


    code.open(file_location);
    string text;
    string number_str, letter_str;
    vector <Token> token_vector;
    Token token_char;
    if (code.is_open())
    {
        while (code.eof() != 1) {
            getline(code, text);

            for (unsigned int i = 0; i < text.length(); i++) {
                switch (state) {
                case START:
                    if (isdigit(text[i])) {
                        number_str = text[i];
                        state = INNUM;
                    }
                    else if (isalpha(text[i])) {
                        letter_str = text[i];
                        state = INID;
                    }
                    else if (text[i] == ':') {
                        state = INASSIGN;
                    }
                    else if (text[i] == '{') {
                        state = INCOMMENT;
                    }
                    else {
                        if (text[i] != ' ') {
                            token_char.set_token(text[i]);
                            token_char.set_type();
                            token_vector.push_back(token_char);
                        }
                    }
                    break;
                case INNUM:
                    if (isdigit(text[i])) {
                        number_str += text[i];
                        state = INNUM;
                    }
                    else if ((text[i] < 65 || (text[i] > 90 && text[i] < 97) || text[i] > 122) || i == 0) {
                        token_char.set_token(number_str, "NUMBER");
                        token_vector.push_back(token_char);
                        state = DONE;
                        prev_state = INNUM;
                        i = i - 1;
                    }
                    else {
                        token_char.set_token("Invalid Number", "Error");
                        token_vector.push_back(token_char);
                    }
                    break;
                case INID:
                    if (isalpha(text[i])) {
                        letter_str += text[i];
                        state = INID;
                    }
                    else {
                        token_char.set_token(letter_str);
                        token_char.set_type();
                        token_vector.push_back(token_char);
                        state = DONE;
                        prev_state = INID;
                        i = i - 1;
                    }
                    break;
                case INASSIGN:
                    if (text[i] == '=') {
                        state = DONE;
                        prev_state = INASSIGN;
                        token_char.set_token(":=", "ASSIGN");
                        token_vector.push_back(token_char);
                    }
                    else {
                        token_char.set_token("Wrong assignment operator", "Error");
                        token_vector.push_back(token_char);
                    }
                    break;
                case INCOMMENT:
                    if (text.find('}') != -1) {
                        state = DONE;
                        prev_state = INCOMMENT;
                        i = text.find('}') + 1;
                    }
                    else {
						token_char.set_token("", "Break");
						token_vector.push_back(token_char);
                    }
                    break;
                case DONE:
                    i = i - 1;
                    state = START;
                    break;
                default:
                    break;
                }
            }

        }
        vector_print(token_vector);
        code.close();
    }
    else
    {
        cout << "ERORR :: NO SUCH FILE !";
    }

}

Token::Token()
{
    value = "NULL";
    type = "NULL";
}

void Token::set_token(string ivalue, string itype)
{
    value = ivalue;
    type = itype;
}

void Token::set_token(char c)
{
    value = c;
}

void Token::set_token(string s)
{
    value = s;
}


void Token::print_token()
{
    cout << value << ", " << type << endl;
}

string Token::get_type()
{
    return type;
}
void Token::set_type()
{
    if (this->value == "if") {
        this->type = "IF";
    }
    else if (this->value == "then") {
        this->type = "THEN";
    }
    else if (this->value == "else") {
        this->type = "ELSE";
    }
    else if (this->value == "end") {
        this->type = "END";
    }
    else if (this->value == "repeat") {
        this->type = "REPEAT";
    }
    else if (this->value == "until") {
        this->type = "UNTIL";
    }
    else if (this->value == "read") {
        this->type = "READ";
    }
    else if (this->value == "write") {
        this->type = "WRITE";
    }
    else if (this->value == "+") {
        this->type = "PLUS";
    }
    else if (this->value == "-") {
        this->type = "MINUS";
    }
    else if (this->value == "*") {
        this->type = "MULTIPLY";
    }
    else if (this->value == "/") {
        this->type = "DIVIDE";
    }
    else if (this->value == "=") {
        this->type = "EQUAL";
    }
    else if (this->value == "<") {
        this->type = "SMALLER THAN";
    }
    else if (this->value == ";") {
        this->type = "SEMI";
    }
    else if (this->value == "(") {
        this->type = "OPEN BRACKET";
    }
    else if (this->value == ")") {
        this->type = "CLOSE BRACKET";
    }
    else if (this->value == "[") {
        this->type = "OPEN SQUARED BRACKET";
    }
    else if (this->value == "]") {
        this->type = "CLOSE SQUARED BRACKET";
    }
    else {
        this->type = "IDENTIFIER";
    }
}
