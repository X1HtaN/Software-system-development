package org.example.rps_lab3;

import java.sql.*;
import java.util.ArrayList;

public class DBConnect {
    private static Connection connection = null;
    private static Statement statement = null;
    private static ResultSet resultSet = null;

    final static String DBUSER = "35zcYNxe8LpiaG3.root";
    final static String DBPWD = "Gp54uAM9VUu55Xvf";
    final static String DBURL = "jdbc:mysql://gateway01.eu-central-1.prod.aws.tidbcloud.com:4000/service";

    public static void start_connect() throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.cj.jdbc.Driver");

        connection = null;
        connection = DriverManager.getConnection(DBURL, DBUSER, DBPWD);
        if(connection != null) {
            System.out.println("Connected to the database successfully");
        } else {
            System.out.println("Failed to connect to database");
        }

        statement = null;
        statement = connection.createStatement();
        if(statement != null) {
            System.out.println("Created statement successfully");
        } else {
            System.out.println("Failed to create statement");
        }
    }

    public static int authorize_user(String username, String password) throws SQLException {
        String query = "SELECT id, password FROM users WHERE username = ?";

        try (PreparedStatement pstmt = connection.prepareStatement(query)) {
            pstmt.setString(1, username);
            ResultSet resultSet = pstmt.executeQuery();

            if (resultSet.next()) {
                String dbPassword = resultSet.getString("password");
                int userId = resultSet.getInt("id");

                if (password.equals(dbPassword)) {
                    System.out.println("DBConnect: пароль верный");
                    return userId;
                } else {
                    System.out.println("DBConnect: неверный пароль");
                    return -1;
                }
            } else {
                return 0;
            }
        } catch (SQLException e) {
            return 0;
        }
    }
}
