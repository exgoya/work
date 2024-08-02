import os
import subprocess

# Trac Wiki 파일이 있는 디렉토리
input_dir = '/Users/goya/git/work/wiki'
# 변환된 rst 파일을 저장할 디렉토리
output_dir = '/Users/goya/git/work/wiki/rst'

if not os.path.exists(output_dir):
    os.makedirs(output_dir)

success_files = []
failed_files = []

for file_name in os.listdir(input_dir):
    if file_name.endswith('.txt'):
        input_file = os.path.join(input_dir, file_name)
        temp_html_file = os.path.join(output_dir, file_name.replace('.txt', '.html'))
        output_file = os.path.join(output_dir, file_name.replace('.txt', '.rst'))
        
        try:
            # Trac Wiki to HTML
            subprocess.run(['pandoc', '-f', 'markdown', '-t', 'html', '-o', temp_html_file, input_file], check=True)
            
            # HTML to reStructuredText
            subprocess.run(['pandoc', '-f', 'html', '-t', 'rst', '-o', output_file, temp_html_file], check=True)
            
            # 중간 HTML 파일 삭제
            os.remove(temp_html_file)
            
            success_files.append(file_name)
        except subprocess.CalledProcessError:
            failed_files.append(file_name)

# 결과 출력
print("성공적으로 변환된 파일들:")
for file in success_files:
    print(file)

print("\n실패한 파일들:")
for file in failed_files:
    print(file)

