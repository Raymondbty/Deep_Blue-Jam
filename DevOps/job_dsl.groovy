pipeline {
    agent any
    options {
        skipStagesAfterUnstable()
    }
    stages {
        stage('Tools') {
            steps {
                script {
                    def cloneUrl = input message: 'Enter the Git URL of the repository to clone', parameters: [string(name: 'GIT_REPOSITORY_URL', defaultValue: '')]
                    sh "git clone ${cloneUrl}"
                }
            }
        }
        stage('SEED') {
            steps {
                script {
                    def gitHubRepo = input message: 'Enter the GitHub repository owner/repo_name (e.g.: "Raymondbty/chocolatine")', parameters: [
                        string(name: 'GITHUB_NAME', defaultValue: ''),
                        string(name: 'DISPLAY_NAME', defaultValue: '')
                    ]
                    def jobScript = """
                        job('${gitHubRepo.DISPLAY_NAME}') {
                            triggers {
                                scm('* * * * *')
                            }
                            scm {
                                github('${gitHubRepo.GITHUB_NAME}')
                            }
                            steps {
                                sh 'make fclean'
                                sh 'make'
                                sh 'make tests_run'
                                sh 'make clean'
                            }
                            wrappers {
                                preBuildCleanup()
                            }
                        }
                    """
                    def jobDslScript = jobScript.stripIndent()
                    jobDslScript = jobDslScript.replaceAll(/\\/, "\\\\\\\\")
                    jobDslScript = jobDslScript.replaceAll(/"/, "\\\\\\\"")
                    jobDslScript = "pipelineJob('${JOB_NAME}') {\n\tnil\n}"
                    jobDslScript = jobDslScript.replaceAll(/'/, "\\\\\\'")
                    jobDslScript = "jobDsl scriptText: \"${jobDslScript}\"\n"
                    pipelineScript(jobDslScript)
                }
            }
        }
    }
}
