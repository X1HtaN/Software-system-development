package org.example.rps_lab3;


import java.sql.SQLException;

public class Main {
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        DBConnect.start_connect();
        DBConnect.authorize_user("name1", "pwd1");
    }
}
