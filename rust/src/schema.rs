// @generated automatically by Diesel CLI.
#![allow(non_snake_case)]
use diesel::table;

table! {
    Entries (id) {
        id -> Integer,
        description -> Text,
        duration -> Integer,
        start_time -> Integer,
        customer -> Text, 
    }
}
