// @generated automatically by Diesel CLI.

use diesel::table;

#[allow(non_snake_case)]
table! {
    Entries (id) {
        id -> Integer,
        description -> Text,
        duration -> Integer,
        start_time -> Integer,
    }
}
