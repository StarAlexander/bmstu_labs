CREATE TABLE students (
    student_id SERIAL PRIMARY KEY,
    full_name TEXT NOT NULL,
    group_number TEXT NOT NULL
);

CREATE TABLE subjects (
    subject_id SERIAL PRIMARY KEY,
    subject_name TEXT NOT NULL
);

CREATE TABLE grades (
    grade_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE,
    subject_id INTEGER REFERENCES subjects(subject_id) ON DELETE CASCADE,
    grade INTEGER CHECK (grade BETWEEN 2 AND 5)
);

CREATE TABLE attendance (
    attendance_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE,
    date_attended DATE NOT NULL,
    status TEXT NOT NULL 
);

CREATE TABLE notes (
    note_id SERIAL PRIMARY KEY,
    student_id INTEGER REFERENCES students(student_id) ON DELETE CASCADE,
    note_text TEXT NOT NULL
);


INSERT INTO students (full_name, group_number) VALUES
('Иванов Иван Иванович', 'М3439'),
('Петров Петр Петрович', 'М3439'),
('Сидоров Сидор Сидорович', 'М3439'),
('Кузнецова Анна Сергеевна', 'М3439'),
('Смирнов Дмитрий Алексеевич', 'М3439'),
('Волкова Екатерина Павловна', 'М3439');


INSERT INTO subjects (subject_name) VALUES
('Математический анализ'),
('Аналитическая геометрия'),
('Информатика');


INSERT INTO grades (student_id, subject_id, grade)
SELECT s.student_id, subj.subject_id, 5 - (s.student_id + subj.subject_id) % 4
FROM students s
CROSS JOIN subjects subj;


INSERT INTO attendance (student_id, date_attended, status)
SELECT s.student_id, '2025-12-10'::date, 'present'
FROM students s
UNION ALL
SELECT s.student_id, '2025-12-11'::date, CASE WHEN s.student_id % 3 = 0 THEN 'absent' ELSE 'present' END
FROM students s;


INSERT INTO notes (student_id, note_text) VALUES
(1, 'Любит информатику'),
(2, 'Нужна помощь по информатике'),
(3, 'Редко посещает занятия по информатике'),
(4, 'Отличник по всем предметам'),
(5, 'Хорошо работает в команде'),
(6, 'Прогресс по информатике');


CREATE INDEX idx_students_group ON students(group_number);
CREATE INDEX idx_grades_student ON grades(student_id);
CREATE EXTENSION IF NOT EXISTS pg_trgm;
CREATE INDEX idx_notes_gin ON notes USING GIN (note_text gin_trgm_ops);


CREATE VIEW student_avg_grades AS
SELECT
    s.student_id,
    s.full_name,
    AVG(g.grade) AS avg_grade
FROM students s
JOIN grades g ON s.student_id = g.student_id
GROUP BY s.student_id, s.full_name;


BEGIN;


INSERT INTO students (full_name, group_number)
VALUES ('Новиков Алексей Викторович', 'М3439');


INSERT INTO grades (student_id, subject_id, grade)
SELECT currval('students_student_id_seq'), subject_id, 4
FROM subjects;

COMMIT;

WITH target AS (SELECT student_id FROM students WHERE student_id = 3)
SELECT * FROM students
WHERE group_number = (SELECT group_number FROM students WHERE student_id = 3)
  AND student_id BETWEEN (SELECT student_id FROM target) - 2 AND (SELECT student_id FROM target) + 3
  AND student_id != (SELECT student_id FROM target)
ORDER BY student_id
LIMIT 5;


SELECT * FROM student_avg_grades WHERE student_id = 3;


SELECT AVG(g.grade) AS avg_informatics
FROM grades g
JOIN subjects s ON g.subject_id = s.subject_id
WHERE s.subject_name = 'Информатика';

SELECT * FROM notes WHERE note_text ILIKE '%информатика%';


BEGIN;
UPDATE attendance
SET status = 'absent'
WHERE student_id = 1 AND date_attended = '2025-12-10';
COMMIT;