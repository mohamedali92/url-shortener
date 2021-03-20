drop table urls;
create table if not exists urls (
                                    short_url text primary key ,
                                    full_url text
);